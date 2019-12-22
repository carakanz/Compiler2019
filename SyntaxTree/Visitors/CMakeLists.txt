# CMakeList.txt: проект CMake для LexicalAnalyz; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project(Visitors VERSION 1.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC
        include/SyntaxTreeDFSVisitor.h
        include/SyntaxTreePrinter.h
        src/SyntaxTreePrinter.cpp
        include/Visitors.h
        src/TypeCheck.cpp
        include/TypeCheck.h )

target_link_libraries(${PROJECT_NAME} SyntaxTree SymbolTable IRTree)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${COMMON_INCLUDES})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER
        include/Visitors.h
        )
