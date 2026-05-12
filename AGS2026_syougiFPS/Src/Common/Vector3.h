#ifndef VECTOR3_H
#define VECTOR3_H

struct Vector3 {
    float x, y, z;

    Vector3();
    Vector3(float _x, float _y, float _z);

    Vector3 operator+(const Vector3& v) const;
    Vector3 operator-(const Vector3& v) const;
    Vector3 operator*(float s) const;

    float length() const;    // ベクトルの長さを取得
    Vector3 normalize() const; // 長さを1にしたベクトルを取得
};

#endif