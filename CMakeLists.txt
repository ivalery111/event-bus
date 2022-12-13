cmake_minimum_required(VERSION 3.15)

project(EventBus VERSION 0.0.1 LANGUAGES CXX)

add_library(event_bus INTERFACE)
target_include_directories(event_bus INTERFACE .)

#add_executable(Runner.out Runner.cpp)

option(ENABLE_TESTING "Enable Testing" OFF)
if(ENABLE_TESTING)
    message("TESTING ON")
    enable_testing()
    add_subdirectory(test)
endif()

