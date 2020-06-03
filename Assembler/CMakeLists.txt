cmake_minimum_required (VERSION 3.8)

project(Assembler VERSION 1.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)


set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${COMMON_INCLUDES} ../Defines)
target_link_libraries(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER
        )

add_subdirectory(Visitors)