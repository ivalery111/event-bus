cmake_minimum_required(VERSION 3.15)

project(EventBus VERSION 0.0.1 LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

include(CompilerFlags)
add_library(project_flags INTERFACE)
set_compiler_flags(project_flags)

include(Sanitizers)
add_library(sanitizers INTERFACE)
enable_sanitizers(sanitizers)

add_library(event_bus INTERFACE)
target_include_directories(event_bus INTERFACE .)
target_link_libraries(event_bus INTERFACE project_flags)

option(ENABLE_TESTING "Enable Testing" OFF)
if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()
