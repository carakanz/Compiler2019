cmake_minimum_required (VERSION 3.8)

project(IRTree VERSION 1.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC
        ../SyntaxTree/Visitors/src/IRTreeTranslator.cpp include/IRTreeNode.h include/IRTreeVisitor.h include/IRTreeStatements.h)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${COMMON_INCLUDES})
target_link_libraries(${PROJECT_NAME} SymbolTable SyntaxTree)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER
        ../SyntaxTree/Visitors/include/IRTreeTranslator.h
        )