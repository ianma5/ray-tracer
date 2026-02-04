#ifndef RAYTRACER_WORLD_H
#define RAYTRACER_WORLD_H
#include <vector>

#include "Camera.h"
#include "Light.h"


class World {
public:
    Camera camera {};

    std::vector<Light> lights {};
    std::vector<std::unique_ptr<Shape>> shapes {};

    float ambient = 0.3f;

    void addShape(std::unique_ptr<Shape> s) {shapes.push_back(std::move(s));}
    void addLight(const Light &l) {lights.push_back(l);}

    World() {}
};


#endif //RAYTRACER_WORLD_H