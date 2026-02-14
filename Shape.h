//
// Created by ian on 2/4/26.
//

#ifndef RAYTRACER_SHAPE_H
#define RAYTRACER_SHAPE_H
#include <cstdint>
#include <iostream>

#include "Ray.h"

struct Shape {
    Vector3 center {}; // center of the shape
    uint32_t color {};
    float diffuseCoefficient = 1.0f;
    float specularCoefficient = 0.5f;
    int shininess {100};
    bool glazed = false;

    Shape(const Vector3 &c, uint32_t co, float dif, float spec, int shiny, bool glazed = false): center(c), color(co), diffuseCoefficient(dif), specularCoefficient(spec), shininess(shiny), glazed(glazed) {};
    virtual ~Shape() {};
    virtual std::pair<bool, float>intersect(const Ray &ray, float min, float max) const = 0;
    virtual Vector3 getNormal(const Vector3& hitPoint) const = 0;
};

struct Sphere : Shape {
    float radius {};
    std::pair<bool, float>intersect(const Ray &ray, float min, float max) const override {
        Vector3 originOffset = ray.origin - center; // calculate the sphere's offset from the ray
        float dP = dot(ray.direction, originOffset); // calculates dot product between ray direction and spheres center (with offset)
        dP *= dP;
        dP = dP - dot(originOffset, originOffset) + (radius * radius); // this is the discriminant
        if (dP < 0) {
            return {false, -1}; // must be positive for there to be a hit
        }
        float t_val = -dot(ray.direction, originOffset) + sqrt(dP);
        float t_val2 = -dot(ray.direction, originOffset) - sqrt(dP);
        // choose nearest valid t
        float t = t_val;
        if (t < min || t > max) {
            t = t_val2;
            if (t < min || t > max)
                return {false, -1};
        }
        return {true, std::min(t_val, t_val2)};
    }
    Vector3 getNormal(const Vector3 &hitPoint) const override {
        return (hitPoint - center);
    };
    Sphere(float r, const Vector3 &c, uint32_t co, float dif, float spec, int shiny, bool glazed = false) : Shape(c, co, dif, spec, shiny, glazed), radius(r) {};
};

struct Plane : Shape {
    Vector3 planeNormal {};
    // need a normal vector, point in question (pixel point?), point on the plane (the center for now)
    // this is an infinite plane, for now ( the floor )
    std::pair<bool, float>intersect(const Ray &ray, float min, float max) const override {
        // t = N dot (P0-origin) / N dot D
        // first calculate division
        Vector3 normal = normalize(planeNormal);
        float divisor = dot(normal, ray.direction);
        if (divisor == 0) return {false, -1}; // if T is zero, there is no hit
        float t = dot(normal, (center - ray.origin)) / divisor;
        if (t < min || t > max)
            return {false, -1};

        return {true, t};
    }
    Vector3 getNormal(const Vector3 & hitPoint) const override {
        return planeNormal;
    };
    Plane(const Vector3 &c, const Vector3 &n, uint32_t co, float dif, float spec, int shiny, bool glazed = false) : Shape(c, co, dif, spec, shiny, glazed), planeNormal(n) {};
};


#endif //RAYTRACER_SHAPE_H