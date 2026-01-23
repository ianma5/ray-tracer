#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H
#include <cstdint>
#include <vector>

#include "Ray.h"
#include "Sphere.h"

class Camera {
public:
    static constexpr int WIDTH{256};
    static constexpr int HEIGHT{256};
    static constexpr float PIXEL_DISTANCE{0.05};

    uint8_t* rayTrace(const std::vector<Sphere> &spheres);
    Ray makeRay(int xi, int yi);


private:
    uint8_t buffer[HEIGHT][WIDTH * 3] {};
    struct val {
        Vector3 viewpoint {0,0,-3};
        Vector3 upVector {0,1,0};
        Vector3 right {};
        Vector3 lookAt {0,0,1};
    };
    val cv {};
};


#endif //RAYTRACER_CAMERA_H