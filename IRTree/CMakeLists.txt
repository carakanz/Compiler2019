cmake_minimum_required (VERSION 3.8)

project(IRTree VERSION 1.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC
        src/IRTreeTranslator.cpp)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${COMMON_INCLUDES})
target_link_libraries(${PROJECT_NAME} SymbolTable)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER
        include/IRTreeTranslator.h
        )