#include "Camera.h"
#include "Light.h"
#include <algorithm>
#include <memory>
#include "Shape.h"


uint8_t* Camera::rayTrace(const std::vector<std::unique_ptr<Shape>> &shapes, const std::vector<Light> &lights) {
    for (int i = 0; i < WIDTH*HEIGHT; i++) {
        Ray ray  = makeRay(i % WIDTH, i / WIDTH); // create the ray for the current pixel
        const Shape *currentShape = nullptr;
        float minT = INFINITY;

        for (int j = 0; j < shapes.size(); j++) {
            const auto *tempShape = shapes[j].get(); // locate the current shape
            std::pair<bool, float> p = tempShape->intersect(ray, 0 , INFINITY); // determine intersection
            if (!p.first) continue; // is not visible to the screen
            if (p.second < minT) { // there is a hit at some point, if it is less than the minimum t (visible to camera)
                currentShape = tempShape; // set the current shape to the temp shape
                minT = p.second; // set minT to the new value
            }
        }
        if (!currentShape) continue; // if there isn't a shape then move onto the next

        float totalLight = 0.3f; // set the ambient light first
        Vector3 hitPoint = ray.origin + (minT * (ray.direction)); // compute the hit point (complete the parametric line equation using the minT)
        Vector3 normal = normalize(currentShape->getNormal(hitPoint)); // compute the normal vector for the shape (orthogonal)

        for (int z = 0; z < lights.size(); z++) { // loop through all scene lights
            const Light* currentLight = &lights[z];
            Vector3 toLight = (currentLight->position - (hitPoint)); // vector pointing from the hit point to the light
            float rSquared = dot(toLight, toLight); // distance (squared) to the light
            float distance = sqrt(rSquared); // actual distance to the light

            Ray toLightRay(hitPoint + normal, toLight / distance); // construct a new ray that travels toward the light source

            bool blocked = false;
            for (int j = 0; j < shapes.size(); j++) { // for all shapes in scene
                const auto *tempShape = shapes[j].get();
                if (tempShape == currentShape) continue; // so the shape doesnt hit itself
                std::pair<bool, float> p = tempShape->intersect(toLightRay, 0 , distance); // determine intersection
                if (p.first) { // if there is a hit traveling the toLightRay that means somethings blocking it
                    blocked = true; // tell the light loop there is a blockage
                    break; // exit the loop
                }
            }
            if (blocked) continue;
            toLight = normalize(toLight);

            totalLight += currentShape->diffuseCoefficient * (lights[z].intensity / (rSquared)) * std::max(0.0f, dot(normal, toLight)); // diffuse

            // now calculate specular
            Vector3 toCameraRay = normalize( 2*dot(normal, toLight)*normal-toLight); // solve for toCameraRay

            // now that we have the vR vector, calculate the specular light and add it to the total light
            float specular = currentShape->specularCoefficient * (lights[z].intensity / rSquared) * std::pow(std::max(0.0f, dot(normalize(ray.origin - hitPoint), toCameraRay)), currentShape->shininess);
            totalLight += specular;
        }

        totalLight = std::clamp(totalLight, 0.0f, 1.0f);

        const uint32_t sphereColor = static_cast<uint32_t>(currentShape->color);
        int x = i % WIDTH; // converts i into x coordinate
        int y = i / WIDTH; // converts i into y coordinate
        int base = x * 3;

        buffer[y][base + 0] = ((sphereColor & 0xFF0000) >> 16) * totalLight; // first byte (red)
        buffer[y][base + 1] = ((sphereColor & 0x00FF00) >> 8) * totalLight;  // second byte ( green)
        buffer[y][base + 2] = (sphereColor & 0x0000FF) * totalLight; // third byte (blue)
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