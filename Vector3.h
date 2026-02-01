//
// Created by ian on 1/23/26.
//

#ifndef RAYTRACER_VECTOR3_H
#define RAYTRACER_VECTOR3_H

#endif //RAYTRACER_VECTOR3_H

struct Vector3 {
    float x{}, y{}, z{};
};

inline Vector3 operator+(const Vector3& a, const Vector3& b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

inline Vector3 operator-(const Vector3& a) {
    return {-a.x, -a.y, -a.z};
}

inline Vector3 operator-(const Vector3& a, const Vector3& b) {
    return {a.x-b.x, a.y-b.y, a.z-b.z};
}

inline Vector3 operator*(const Vector3& a, const float b) {
    return {a.x * b, a.y * b, a.z * b};
}

inline Vector3 operator*(float b, const Vector3& a) {
    return {a.x * b, a.y * b, a.z * b};
}

inline float dot(const Vector3& a, const Vector3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vector3 operator/(const Vector3& a, const float b) {
    return {a.x / b, a.y / b, a.z / b};
}