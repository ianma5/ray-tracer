cmake_minimum_required(VERSION 4.1)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(raytracer main.cpp
        main.cpp
        Ray.h
        Vector3.h
        Sphere.h
        Camera.cpp
        Camera.h
        World.cpp
        World.h)
