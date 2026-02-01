#pragma once
#include <cmath>

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
        Vector3 originOffset = ray.origin - center;
        float num = dot(ray.direction, originOffset);
        num *= num;
        num = num - dot(originOffset, originOffset) + (radius * radius);
        if (num < 0) {
            return {false, -1};
        }
        float t_val = -dot(ray.direction, originOffset) + sqrt(num);
        float t_val2 = -dot(ray.direction, originOffset) - sqrt(num);
        return {true, std::min(t_val, t_val2)};
    }
    Sphere(Vector3 pos, int r, Color c) : center(pos), color{c}, radius(r) {}
};