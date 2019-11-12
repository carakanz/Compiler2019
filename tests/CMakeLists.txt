message("Include gtest: " ${gtest_SOURCE_DIR})

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

function(execut_test TestName)
    add_executable(${TestName}
            ${PROJECT_SOURCE_DIR}/tests/RunUnitTest.cpp
            ${ARGN})
    target_sources(RunAllUnitTests
            PUBLIC
            ${ARGN})
    message("Add test " ${TestName})
endfunction()

function(add_test_libraries TestName)
    target_link_libraries(${TestName} gtest
            gtest_main
            ${ARGN})
    target_link_libraries(RunAllUnitTests
            ${ARGN})
endfunction()

enable_testing()

add_executable(RunAllUnitTests
        ${PROJECT_SOURCE_DIR}/tests/RunUnitTest.cpp)
target_link_libraries(RunAllUnitTests gtest
        gtest_main)

execut_test(ParserUnitTest
        ${PROJECT_SOURCE_DIR}/tests/ParserUnitTest.cpp)
add_test_libraries(ParserUnitTest BisonBuilder)

include_directories(${COMMON_INCLUDES})

add_test(UnitTests RunAllUnitTests)
