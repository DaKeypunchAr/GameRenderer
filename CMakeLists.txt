cmake_minimum_required(VERSION 3.28...3.29)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(GameRenderer VERSION 1.0.0 LANGUAGES CXX)

add_library(GRenderer "src/Context.cpp" "src/ShaderProgram.cpp" "src/Renderer.cpp")
set(GLFW_LIBRARY_TYPE STATIC)
set(GLFW_BUILD_SHARED_LIBS OFF)

add_subdirectory("glew-2.1.0/build/cmake")
add_subdirectory("glfw-3.4")
add_subdirectory("glm")

target_link_libraries(GRenderer PUBLIC glew_s glfw glm)
target_include_directories(GRenderer PUBLIC "include")

add_subdirectory(Tests)

get_filename_component(PROJECT_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)
configure_file("src/root.hpp.in" root.hpp @ONLY)

target_include_directories(GRenderer PUBLIC 
    "include"
    "glew-2.1.0/include"
    "glfw-3.4/include"
    "${CMAKE_CURRENT_BINARY_DIR}"
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(GRenderer PUBLIC _DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(GRenderer PUBLIC _RELEASE)
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    target_compile_definitions(GRenderer PUBLIC _32BIT)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    target_compile_definitions(GRenderer PUBLIC _64BIT)
endif()