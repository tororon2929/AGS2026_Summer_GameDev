#ifndef VECTOR3_H
#define VECTOR3_H

#include <DxLib.h>

struct Vector3
{
    float x;
    float y;
    float z;

    Vector3();
    Vector3(float _x, float _y, float _z);

    Vector3 operator+(const Vector3& v) const;
    Vector3 operator-(const Vector3& v) const;
    Vector3 operator*(float s) const;

    float length() const;

    Vector3 normalize() const;

    float dot(const Vector3& v) const;

    VECTOR ToVECTOR() const;

    static Vector3 Zero();
};

#endif