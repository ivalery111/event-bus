#include "EventBus.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

static int count = 0;

TEST_CASE("Publusher Die") {
    struct EventInc : public Event {};

    struct Inc {
        void inc_count(EventInc& inc) {
            (void)inc; // unused
            ++count;
        }
    };

    Inc *inc = new Inc();

    EventBus bus;
    bus.subscribe<Inc, EventInc>(inc, &Inc::inc_count);

    bus.publish<EventInc>({});
    REQUIRE(count == 1);

    delete inc;

    bus.publish<EventInc>({});
    REQUIRE(count == 2);
}
