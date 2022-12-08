cmake_minimum_required(VERSION 3.14)
project(wm)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB_RECURSE t9_sources t9/*.cpp)
file(GLOB_RECURSE sources src/*.cpp)
file(GLOB_RECURSE client_sources src-client/*.cpp)

source_group(TREE ${CMAKE_SOURCE_DIR}/t9 FILES ${t9_sources})
source_group(TREE ${CMAKE_SOURCE_DIR}/src FILES ${sources})
source_group(TREE ${CMAKE_SOURCE_DIR}/src-client FILES ${client_sources})

add_library(t9 STATIC ${t9_sources})
target_compile_features(t9 PUBLIC cxx_std_17)
target_compile_options(t9 PUBLIC /W4 /utf-8)
target_compile_definitions(t9 PUBLIC _UNICODE)
target_include_directories(t9 PUBLIC .)

add_library(${PROJECT_NAME} SHARED ${sources})
target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.h)
target_include_directories(${PROJECT_NAME} PUBLIC src)
target_link_libraries(${PROJECT_NAME} PRIVATE t9)

add_executable(${PROJECT_NAME}-client WIN32 ${client_sources})
target_precompile_headers(${PROJECT_NAME}-client PRIVATE src-client/pch.h)
target_include_directories(${PROJECT_NAME}-client PRIVATE src-client)
target_link_libraries(${PROJECT_NAME}-client PRIVATE
    ${PROJECT_NAME}
    t9)