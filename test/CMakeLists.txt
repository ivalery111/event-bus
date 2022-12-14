add_library(catch INTERFACE)
target_include_directories(catch INTERFACE .)

add_executable(test_publish_subscribe test_publish_subscribe.cpp)
target_link_libraries(test_publish_subscribe event_bus catch project_flags stdc++ sanitizers)
add_test(
    NAME test_publish_subscribe
    COMMAND $<TARGET_FILE:test_publish_subscribe>
)

add_executable(test_subscriber_die test_subscriber_die.cpp)
target_link_libraries(test_subscriber_die event_bus catch project_flags stdc++ sanitizers)
add_test(
    NAME test_subscriber_die
    COMMAND $<TARGET_FILE:test_subscriber_die>
)

