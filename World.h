#ifndef RAYTRACER_WORLD_H
#define RAYTRACER_WORLD_H
#include <vector>

#include "Camera.h"
#include "Light.h"
#include "Sphere.h"


class World {
public:
    Camera camera {};

    std::vector<Light> lights {};
    std::vector<Sphere> spheres {};

    void addSphere(const Sphere &s) {spheres.push_back(s);}
    void addLight(const Light &l) {lights.push_back(l);}

    World() {}
};


#endif //RAYTRACER_WORLD_H