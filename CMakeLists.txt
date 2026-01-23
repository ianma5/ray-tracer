cmake_minimum_required(VERSION 4.1)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)


add_executable(raytracer
        main.cpp
        Ray.h
        Vector3.h
        Sphere.h
        Camera.cpp
        Camera.h
        World.cpp
        World.h)

target_link_libraries(raytracer
        OpenGL::GL
        glfw
        GLEW::GLEW
)