cmake_minimum_required(VERSION 4.0)
project(Arkade)

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
        GIT_TAG "master"
        GIT_PROGRESS ON
)

FetchContent_MakeAvailable(raylib)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
set(INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/")

file(GLOB_RECURSE SIMPLE_SERIAL_SRC "${CMAKE_CURRENT_LIST_DIR}/extern/simple_serial_port/*.cpp")
list(APPEND SRC ${SIMPLE_SERIAL_SRC})

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE
        ${INCLUDE}
        ${CMAKE_CURRENT_LIST_DIR}/extern/simple_serial_port/simple-serial-port/
)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Setting ASSETS_PATH
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Resources/") # Set the asset path macro to the absolute path on the dev machine
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./Resources") # Set the asset path macro in release mode to a relative path that assumes the assets folder is in the same directory as the game executable