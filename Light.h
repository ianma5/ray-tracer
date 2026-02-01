//
// Created by ian on 1/31/26.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

#include "Vector3.h"

struct Light {
    Vector3 position {};
    float intensity {};

    Light(const Vector3 position, const float intensity) : position(position), intensity(intensity) {}
};




#endif //RAYTRACER_LIGHT_H