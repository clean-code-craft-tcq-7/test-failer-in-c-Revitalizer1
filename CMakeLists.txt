cmake_minimum_required(VERSION 3.14)
project(StrongTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()


file(GLOB PROD_SOURCES "src/*.c")
file(GLOB TEST_SOURCES "test/*.cpp")
add_executable(strong_tests ${PROD_SOURCES} ${TEST_SOURCES})


target_compile_definitions(strong_tests PRIVATE TEST_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(
  strong_tests
  GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(strong_tests)
