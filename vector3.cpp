#include "vector3.hpp"

Vector3::Vector3(double _x, double _y, double _z) {
    x = _x;
    y = _y;
    z = _z;
}

double Vector3::getX() const {
    return x;
}

double Vector3::getY() const {
    return y;
}

double Vector3::getZ() const {
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