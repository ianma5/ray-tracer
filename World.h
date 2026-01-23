#ifndef RAYTRACER_WORLD_H
#define RAYTRACER_WORLD_H
#include <vector>

#include "Camera.h"
#include "Sphere.h"


class World {
public:
    Camera camera {};

    void addSphere(Sphere s);
    std::vector<Sphere> spheres;
};


#endif //RAYTRACER_WORLD_H