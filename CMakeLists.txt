cmake_minimum_required(VERSION 3.20)

project(Traffic_hour)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(googletest
                    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
                    DOWNLOAD_EXTRACT_TIMESTAMP TRUE)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(Traffic_hour
                src/main.cpp
                src/parser.cpp
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
    tests/test.cpp
)

target_link_libraries(
    testing
    PRIVATE
    GTest::gtest_main

)

include(GoogleTest)

gtest_add_tests(TARGET testing)