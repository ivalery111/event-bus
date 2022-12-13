#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <algorithm>
#include <iostream>

struct Event {
    bool handled{false};
};

class EventDispatcher {
    public:
        virtual ~EventDispatcher() = default;
        inline void dispatch(Event& event) const {
            invoke_handler(event);
        }
    private:
        virtual void invoke_handler(Event& event) const = 0;
};

template <typename Receiver, typename EventType>
class EventHandler : public EventDispatcher {
    public:
        using HandlerFunc = void(Receiver::*)(EventType&);

        EventHandler(Receiver *receiver, HandlerFunc handler_func)
            : receiver_{receiver},
              handler_func_{handler_func}
        {}

        void invoke_handler(Event& event) const override {
            (receiver_->*handler_func_)(static_cast<EventType&>(event));
        }

        bool operator==(const EventHandler<Receiver, EventType>& rhs) const {
            return (receiver_     == rhs.receiver_) &&
                   (handler_func_ == rhs.handler_func_);
        }

        bool operator==(Receiver* rhs) const {
            return receiver_ == rhs;
        }

    private:
        Receiver   *receiver_;
        HandlerFunc handler_func_;
};

class EventBus {
    public:
        using Dispatcher = std::unique_ptr<EventDispatcher>;
        using HandlerList = std::vector<Dispatcher>;

        EventBus()                           = default;
        EventBus(const EventBus&)            = delete;
        EventBus& operator=(const EventBus&) = delete;

        template <typename EventType>
        void publish(EventType&& event) {
            auto entry = subscribers_.find(typeid(EventType));
            if (entry != subscribers_.end()) {
                for (const auto& handler : entry->second) {
                    if (event.handled) {
                        return;
                    }
                    handler->dispatch(event);
                }
            }
        }

        template <typename Receiver, typename EventType>
        void subscribe(Receiver* receiver, void(Receiver::* handler_func)(EventType&)) {
            HandlerList& handlers = subscribers_[typeid(EventType)];
            handlers.emplace_back(
                std::make_unique<EventHandler<Receiver, EventType>>(receiver, handler_func)
            );
        }

        template <typename Receiver, typename EventType>
        void unsubscribe(Receiver* receiver, void(Receiver::* handler_func)(EventType&)) {
            auto entry = subscribers_.find(typeid(EventType));
            if (entry != subscribers_.end()) {
                const EventHandler<Receiver, EventType> tmp{receiver, handler_func};
                HandlerList& handlers = entry->second;
                handlers.erase(
                    std::remove_if(
                        handlers.begin(),
                        handlers.end(),
                        [&](const auto& handler) {
                            using T = EventHandler<Receiver, EventType>;
                            return *static_cast<T*>(handler.get()) == tmp;
                        }
                    ), handlers.end()        
                );
            }
        }

        template <typename Receiver>
        void unsubscribe_all(Receiver* receiver) {
            for (auto& [_, handlers] : subscribers_) {
                handlers.erase(
                    std::remove_if(
                        handlers.begin(),
                        handlers.end(),
                        [&](const auto& handler) {
                            using T = EventHandler<Receiver, Event>;
                            return *static_cast<T*>(handler.get()) == receiver;
                        }
                    ), handlers.end()
                );
            }
        }

    private:
        std::unordered_map<std::type_index, HandlerList> subscribers_;
};

