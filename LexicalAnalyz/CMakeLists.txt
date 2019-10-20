# CMakeList.txt: проект CMake для LexicalAnalyz; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project(LexicalAnalyz VERSION 1.0 LANGUAGES CXX)

find_package(FLEX REQUIRED)

if(FLEX_FOUND)
    message("Find flex version " ${FLEX_VERSION})
else()
    message("Cannot find flex")
endif(FLEX_FOUND)

# Создаём специальный таргет, который генерирует lex.yy.cc в папке билда
flex_target(flex_scanner scanner.ll ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cc)
# Сгенерированный файл записывается в переменную FLEX_flex_scanner_OUTPUTS,
# можем использовать её, как исходный файл

message("Cannot find flex")

add_library(${PROJECT_NAME} SHARED
        src/LexicalAnalyz.cpp
        ${FLEX_flex_scanner_OUTPUTS}
        include/Tokens.h)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_INCLUDES})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER
        include/LexicalAnalyz.h
        )
