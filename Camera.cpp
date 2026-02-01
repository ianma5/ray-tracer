#include "Camera.h"

#include "Light.h"
#include <algorithm>


uint8_t* Camera::rayTrace(const std::vector<Sphere> &spheres, const std::vector<Light> &lights) {
    for (int i = 0; i < WIDTH*HEIGHT; i++) {
        Ray ray  = makeRay(i % WIDTH, i / WIDTH); // form the ray for the current pixel
        const Sphere *currentSphere = nullptr;
        float st = INFINITY;

        for (int j = 0; j < spheres.size(); j++) {
            const Sphere *tsphere = &spheres[j]; // locate the current sphere
            std::pair<bool, float> p = tsphere->intersect(ray, 0 , INFINITY); // determine intersection
            if (!p.first) continue; // is not visible to the screen
            if (p.second < st) {
                currentSphere = tsphere;
                st = p.second;
            }
        }
        if (!currentSphere) continue;

        float Ld = 0.3f;
        Vector3 line = ray.origin + (st * ray.direction);

        for (int z = 0; z < lights.size(); z++) {
            const Light* currentLight = &lights[z];
            Vector3 vL = normalize(currentLight->position - (line)); // calculate the direction from hit point to light
            Vector3 normal = normalize(line - currentSphere->center);

            Ld += currentSphere->kd * lights[z].intensity * std::max(0.0f, dot(normal, vL));
        }

        Ld = std::clamp(Ld, 0.0f, 1.0f);

        const uint32_t sphereColor = static_cast<uint32_t>(currentSphere->color);
        int x = i % WIDTH; // converts i into x coordinate
        int y = i / WIDTH; // converts i into y coordinate
        int base = x * 3;

        buffer[y][base + 0] = ((sphereColor & 0xFF0000) >> 16) * Ld; // first byte (red)
        buffer[y][base + 1] = ((sphereColor & 0x00FF00) >> 8) * Ld;  // second byte ( green)
        buffer[y][base + 2] = (sphereColor & 0x0000FF) * Ld; // third byte (blue)
    }
    return buffer[0];
}

Ray Camera::makeRay(int xi, int yi) {
    Vector3 origin = cv.viewpoint + (cv.right * -(((WIDTH/2) - xi) * PIXEL_DISTANCE)) + (cv.upVector * (((HEIGHT/2) - yi) * -PIXEL_DISTANCE));
    Vector3 direction = cv.lookAt;
    direction = direction / sqrt(dot(direction, direction));
    Ray ray = Ray(origin, direction);
    return ray;
}