add_library(catch INTERFACE)
target_include_directories(catch INTERFACE .)

add_executable(test_publish_subscribe test_publish_subscribe.cpp)
target_link_libraries(test_publish_subscribe event_bus catch)
add_test(
    NAME test_publish_subscribe
    COMMAND $<TARGET_FILE:test_publish_subscribe>
)

