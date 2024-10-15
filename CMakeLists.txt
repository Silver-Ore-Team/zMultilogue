cmake_minimum_required(VERSION 3.25)
set(PROJECT_VERSION_CMAKE "0.0.5")
project(zMultilogue VERSION "${PROJECT_VERSION_CMAKE}" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(GOTHIC_API_G1  ON)
set(GOTHIC_API_G1A OFF)
set(GOTHIC_API_G2  OFF)
set(GOTHIC_API_G2A ON)
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



add_library(zMultilogue SHARED)
target_link_libraries(zMultilogue PRIVATE union_api_lib gothic_api)
target_include_directories(zMultilogue PRIVATE src)
target_include_directories(zMultilogue PRIVATE BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/userapi)
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp")
target_sources(zMultilogue PRIVATE ${SOURCES})


target_compile_options(zMultilogue PRIVATE
        /W4 /permissive- /std:c++latest /Zc:__cplusplus /Zc:preprocessor /utf-8
        /experimental:external /external:W0 /external:anglebrackets /external:templates-
        /external:I ${CMAKE_BINARY_DIR}/_deps
)


install(FILES $<TARGET_RUNTIME_DLLS:${CMAKE_PROJECT_NAME}> "${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.dll" TYPE BIN)

configure_file("${CMAKE_SOURCE_DIR}/vdf/script.vs.in" "${CMAKE_BINARY_DIR}/script.vs")

install(FILES $<TARGET_RUNTIME_DLLS:${CMAKE_PROJECT_NAME}> "${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.dll" TYPE BIN)
install(FILES "${CMAKE_BINARY_DIR}/script.vs" DESTINATION "${CMAKE_INSTALL_PREFIX}")
install(SCRIPT "${CMAKE_SOURCE_DIR}/vdf/vdf.cmake")
install(CODE "execute_process(COMMAND ${CMAKE_SOURCE_DIR}/vdf/GothicVDFS.exe /B \"${CMAKE_INSTALL_PREFIX}/script.vs\" WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}\")")

string(REPLACE "build" "install" INSTALL_DIR "${CMAKE_BINARY_DIR}")
add_custom_target(${CMAKE_PROJECT_NAME}_vdf ALL
        COMMAND ${CMAKE_COMMAND} --install ${CMAKE_BINARY_DIR} --prefix ${INSTALL_DIR}
        DEPENDS ${CMAKE_PROJECT_NAME}
        COMMENT "Run install to build VDF")
