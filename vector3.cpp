#include "vector3.hpp"

Vector3::Vector3(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
}

float Vector3::getX() const {
    return x;
}

float Vector3::getY() const {
    return y;
}

float Vector3::getZ() const {
    return z;
}

void Vector3::operator+=(const Vector3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
}

void Vector3::operator-=(const Vector3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
}