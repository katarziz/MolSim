#fetch gtest
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
#collect test and source files
file(GLOB_RECURSE MY_TEST
        "${PROJECT_SOURCE_DIR}/test/*.cpp"
        # header don't need to be included but this might be necessary for some IDEs
        "${PROJECT_SOURCE_DIR}/test/*.h"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.h"
)
#remove source files with main() methods &XML Reader
list(REMOVE_ITEM MY_TEST "${PROJECT_SOURCE_DIR}/src/MolSim.cpp")
add_executable(Test ${MY_TEST})
#target setup similar to MolSim
target_include_directories(Test
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/libxsd
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/test
)
target_link_libraries(Test
        PUBLIC
        xerces-c
        GTest::gtest_main
        spdlog::spdlog
)
include(GoogleTest)
include(${CMAKE_SOURCE_DIR}/cmake/modules/spdlog.cmake)
gtest_discover_tests(Test)
