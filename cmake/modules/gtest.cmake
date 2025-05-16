#fetch gtest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
#collect test files
file(GLOB_RECURSE MY_TEST
        "${PROJECT_SOURCE_DIR}/test/*.cpp"
        # header don't need to be included but this might be necessary for some IDEs
        "${PROJECT_SOURCE_DIR}/test/*.h"
)
add_executable(Test ${MY_TEST})
target_link_libraries(
        Test
        GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(Test)
