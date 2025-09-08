cmake_minimum_required(VERSION 3.10)
project(test_failer VERSION 1.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

# Add source files
set(SOURCE_FILES
    src/tshirts.c
    src/misaligned.c
    src/weatherreport.c
)

# Add test files
set(TEST_FILES
    test/test_tshirts.cpp
    test/test_misaligned.cpp
    test/test_weatherreport.cpp
    test/main_test.cpp
)

# Add the main test executable
add_executable(strong_tests ${TEST_FILES})
target_include_directories(strong_tests PRIVATE src)
target_sources(strong_tests PRIVATE ${SOURCE_FILES})
target_link_libraries(strong_tests PRIVATE gtest gmock)

# Enable testing
enable_testing()
add_test(NAME strong_tests COMMAND strong_tests)