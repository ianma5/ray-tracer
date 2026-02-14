#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H
#include <memory>
#include <vector>

#include "Light.h"
#include "Ray.h"
#include "Shape.h"

class Camera {
public:
    static constexpr int WIDTH{512};
    static constexpr int HEIGHT{512};
    static constexpr float PIXEL_DISTANCE{0.03};

    uint8_t* rayTrace(const std::vector<std::unique_ptr<Shape>> &shapes, const std::vector<Light> &lights); // return rgb array
    std::tuple<float, float, float> rayTrace(const Ray &ray, const std::vector<std::unique_ptr<Shape>> &shapes, const std::vector<Light> &lights, int n); // recursive ray tracing

    Ray makeRay(int xi, int yi);

private:
    uint8_t buffer[HEIGHT][WIDTH * 3] {};
    struct val {
        Vector3 viewpoint {0,3.75f,-5.0};
        Vector3 upVector {0,1,0};
        Vector3 right {1,0,0};
        Vector3 lookAt {0,-0.3f,1};
    };
    val cv {};
};


#endif //RAYTRACER_CAMERA_H