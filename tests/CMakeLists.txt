# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
message("Include gtest: " ${gtest_SOURCE_DIR})

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

execut_test(RunLexicalAnalyzUnitTest
        ${PROJECT_SOURCE_DIR}/tests/LexicalAnalyzUnitTest.cpp)
add_test_libraries(RunLexicalAnalyzUnitTest
        FlexBuilder)

add_test(UnitTests RunAllUnitTests)
