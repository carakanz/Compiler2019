# CMakeList.txt: проект CMake для LexicalAnalyz; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project(FlexBuilder VERSION 1.0 LANGUAGES CXX)

find_package(FLEX REQUIRED)
message("Find flex version: " ${FLEX_VERSION})

# Создаём специальный таргет, который генерирует lex.yy.cc в папке билда
flex_target(flex_scanner scanner.ll ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cc)
# Сгенерированный файл записывается в переменную FLEX_flex_scanner_OUTPUTS,
# можем использовать её, как исходный файл

add_library(${PROJECT_NAME} SHARED
        ${FLEX_flex_scanner_OUTPUTS}
        src/FlexAnalyzerBuilder.cpp)

target_link_libraries(${PROJECT_NAME} LexicalAnalyz)
target_include_directories(${PROJECT_NAME} PUBLIC
        ../LexicalAnalyz/include)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_INCLUDES})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER
        include/FlexAnalyzerBuilder.h
        )
