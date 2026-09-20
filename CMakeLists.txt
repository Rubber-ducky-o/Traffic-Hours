cmake_minimum_required(VERSION 3.20)

project(Traffic_hour)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(googletest
                    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
                    DOWNLOAD_EXTRACT_TIMESTAMP TRUE)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(Traffic_hour
                src/parser.h
                src/Graph.h
                src/main.cpp
                src/parser.cpp
                src/Graph.cpp
                src/algorithm.cpp
                )


find_package(CURL REQUIRED)
find_package(JsonCpp CONFIG REQUIRED)

target_link_libraries(
    Traffic_hour
    PRIVATE
    CURL::libcurl
    JsonCpp::JsonCpp
)

enable_testing()

add_executable(
    testing
    tests/test_Graph.cpp
    tests/test_algorithms.cpp

    src/algorithm.cpp
    src/Graph.cpp
)

target_include_directories(testing PRIVATE src)

target_link_libraries(
    testing
    PRIVATE
    GTest::gtest_main

)

include(GoogleTest)
gtest_discover_tests(testing)