//
// Created by ian on 1/23/26.
//
#include <cmath>
#pragma once

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#endif //RAYTRACER_SPHERE_H


struct Sphere {
    float radius;
    Vector3 center;

    enum class Color: int {
        red = 0xFF0000,
        green = 0x00FF00,
        blue = 0x0000FF,
    };
    Color color;
    std::pair<bool, float> intersect(const Ray &ray, float min, float max) const {
        float num = dot(ray.direction, ray.origin);
        num *= num;
        num = num - dot(ray.origin, ray.origin) + 1;
        if (num < 0) {
            return {false, -1};
        }
        float t_val = -dot(ray.direction, ray.origin) + sqrt(num);
        float t_val2 = -dot(ray.direction, ray.origin) - sqrt(num);
        return {true, std::min(t_val, t_val2)};
    }
};