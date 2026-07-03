cmake_minimum_required(VERSION 3.10)
project(callisto_engine VERSION 0.1.0)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(callisto_engine 
    src/main.cpp
    src/celestialBody.cpp 
    src/rendering.cpp
    src/math.cpp
    src/scene.cpp
    src/camera.cpp
    src/star.cpp
    external/glad/src/glad.c
    external/glad/include/glad/glad.h

)

target_link_libraries(callisto_engine 
    glfw
    OpenGL::GL
)
target_include_directories(callisto_engine PRIVATE external/glad/include)
target_include_directories(callisto_engine PRIVATE include)
