cmake_minimum_required(VERSION 3.25)
project(zMultilogue VERSION 0.0.1 LANGUAGES CXX)

set(PLUGIN_NAME zMultilogue)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        union-api
        GIT_REPOSITORY https://gitlab.com/union-framework/union-api.git
        GIT_TAG        21508ea42aad44c7c6fea4ae06ffc159ec85e69e
)
FetchContent_Declare(
        gothic-api
        GIT_REPOSITORY https://gitlab.com/union-framework/gothic-api.git
        GIT_TAG        a6a66de7386f990c30fec41019d27053372058f2
)
FetchContent_MakeAvailable(union-api)
FetchContent_MakeAvailable(gothic-api)

add_library(${PLUGIN_NAME} SHARED)
target_link_libraries(${PLUGIN_NAME} PRIVATE union_api_lib gothic_api)
target_include_directories(${PLUGIN_NAME} PRIVATE src)
target_include_directories(${PLUGIN_NAME} PRIVATE BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/userapi)
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp")
target_sources(${PLUGIN_NAME} PRIVATE ${SOURCES})

target_compile_options(${PLUGIN_NAME} PRIVATE
        /permissive- /std:c++latest /Zc:__cplusplus /Zc:preprocessor /utf-8
        /experimental:external /external:W0 /external:anglebrackets
        /external:I ${CMAKE_BINARY_DIR}/_deps/gothic-api-src
)
