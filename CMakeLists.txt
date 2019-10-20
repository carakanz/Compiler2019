# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)
project (Compiler2019 VERSION 1.0 LANGUAGES CXX)
get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

option(MYLIB_TESTING "Включить модульное тестирование" ON)
option(MYLIB_COVERAGE "Включить измерение покрытия кода тестами" OFF)

add_compile_options(
#        -Werror

        -Wall
        -Wextra
        -Wpedantic

        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wctor-dtor-privacy
        -Wenum-compare
        -Wfloat-equal
        -Wnon-virtual-dtor
#        -Wold-style-cast
        -Woverloaded-virtual
        -Wredundant-decls
        -Wsign-conversion
        -Wsign-promo
)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_subdirectory(library)
add_subdirectory(LexicalAnalyz)

message("Include gtest: " ${gtest_SOURCE_DIR})

enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(RunUnitTests
        ${PROJECT_SOURCE_DIR}/tests/LexicalAnalyzUnitTest.cpp)

target_link_libraries(RunUnitTests gtest gtest_main)

target_link_libraries(RunUnitTests LexicalAnalyz)

add_test(UnitTests RunUnitTests)
