//
// Created by ian on 1/23/26.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H
#include "Vector3.h"
#pragma once

#endif //RAYTRACER_RAY_H

struct Ray {
    Vector3 origin;
    Vector3 direction;

    Ray(Vector3 o, Vector3 d) : origin(o), direction(d) {}
};