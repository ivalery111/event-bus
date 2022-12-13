#include "EventBus.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

static int count = 0;

TEST_CASE("PublishSubscribeTest") {
    struct EventIncrementator : public Event {};
    
    struct Incrementator {
        void increment_count(EventIncrementator& incrementator) {
            ++count;
        }
    };

    Incrementator incrementator;

    EventBus bus;
    bus.subscribe<Incrementator, EventIncrementator>(&incrementator, &Incrementator::increment_count);

    bus.publish<EventIncrementator>({});
    bus.publish<EventIncrementator>({});

    REQUIRE(count == 2);
}

