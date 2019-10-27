# CMakeList.txt: проект CMake для LexicalAnalyz; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project(SyntaxAnalyz VERSION 1.0 LANGUAGES CXX)

find_package(BISON REQUIRED)
message("Find bison version: " ${BISON_VERSION})

# Создаём специальный таргет, который генерирует parser.cc в папке билда
flex_target(bison_parser parser.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cc)
# Сгенерированный файл записывается в переменную FLEX_flex_scanner_OUTPUTS,
# можем использовать её, как исходный файл

add_library(${PROJECT_NAME} SHARED
        ${BISON_bison_parser_OUTPUTS}
        src/BisonBuilder.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
        ../LexicalAnalyz/include)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_INCLUDES})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER
        include/BisonBuilder.h
        )
