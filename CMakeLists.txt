cmake_minimum_required(VERSION 3.15)
project(c-xplorer)

# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 4.2.0
    )
    FetchContent_MakeAvailable(raylib)
endif()

# raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG v4.2.5
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
     "src/*.hpp"
     "src/*.cpp"
)

add_executable(${PROJECT_NAME} ${SRC} ${RESOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
)