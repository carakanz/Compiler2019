# CMakeList.txt: проект CMake для LexicalAnalyz; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project(BisonBuilder VERSION 1.0 LANGUAGES CXX)

find_package(FLEX REQUIRED)
message("Find flex version: " ${FLEX_VERSION})

find_package(BISON REQUIRED)
message("Find bison version: " ${BISON_VERSION})

flex_target(flex_scanner scanner.ll ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cc)
bison_target(bison_parser parser.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cc COMPILE_FLAGS -v)
add_flex_bison_dependency(flex_scanner bison_parser)

add_library(${PROJECT_NAME} SHARED
        ${FLEX_flex_scanner_OUTPUTS}
        ${BISON_bison_parser_OUTPUTS}
        src/Builder.cpp)

target_link_libraries(${PROJECT_NAME} SyntaxTree)
target_include_directories(${PROJECT_NAME} PUBLIC ${COMMON_INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_INCLUDES})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER
        include/Builder.h)