#include "Camera.h"

#include <iostream>

uint8_t* Camera::rayTrace(const std::vector<Sphere> &spheres) {
    for (int i = 0; i < WIDTH*HEIGHT; i++) {
        Ray ray = makeRay(i % WIDTH, i / WIDTH); // form the ray for the current pixel
        for (int j = 0; j < spheres.size(); j++) {
            const Sphere *currentSphere = &spheres[j];
            std::pair<bool, float> p = currentSphere->intersect(ray, 0 , INFINITY);
            if (!p.first) continue;

            const uint32_t sphereColor = static_cast<uint32_t>(currentSphere->color);
            int x = i % WIDTH; // converts i into x coordinate
            int y = i / WIDTH; // converts i into y coordinate
            int base = x * 3;

            buffer[y][base + 0] = (sphereColor & 0xFF0000) >> 16; // first byte (red)
            buffer[y][base + 1] = (sphereColor & 0x00FF00) >> 8;  // second byte ( green)
            buffer[y][base + 2] = (sphereColor & 0x0000FF); // third byte (blue)
            // buffer[y][x*3 + 0] = 255;
            // buffer[y][x*3 + 1] = 255;
            // buffer[y][x*3 + 2] = 255;

        }
    }
    return buffer[0];
}

Ray Camera::makeRay(int xi, int yi) {
    Vector3 origin = cv.viewpoint + (cv.right * -(((WIDTH/2) - xi) * PIXEL_DISTANCE)) + (cv.upVector * (((HEIGHT/2) - yi) * PIXEL_DISTANCE));
    Vector3 direction = cv.lookAt;
    direction = direction / sqrt(dot(direction, direction));
    Ray ray = Ray(origin, direction);
    return ray;
}