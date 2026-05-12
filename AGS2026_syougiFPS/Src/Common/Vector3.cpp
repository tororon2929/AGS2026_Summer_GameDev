#include "Vector3.h"
#include <cmath>

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
Vector3::Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

Vector3 Vector3::operator+(const Vector3& v) const { return { x + v.x, y + v.y, z + v.z }; }
Vector3 Vector3::operator-(const Vector3& v) const { return { x - v.x, y - v.y, z - v.z }; }
Vector3 Vector3::operator*(float s) const { return { x * s, y * s, z * s }; }

float Vector3::length() const { return std::sqrt(x * x + y * y + z * z); }

Vector3 Vector3::normalize() const {
    float len = length();
    if (len > 0.0001f) return { x / len, y / len, z / len };
    return { 0, 0, 0 };
}