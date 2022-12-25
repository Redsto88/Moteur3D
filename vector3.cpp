#include <stdexcept>

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

void Vector3::operator*=(const float& f) {
    x *= f;
    y *= f;
    z *= f;
}

void Vector3::operator/=(const float& f) {
    if (f == 0) {
        throw std::invalid_argument("Division by zero");
    }
    x /= f;
    y /= f;
    z /= f;
}

Vector3 operator+(const Vector3& v1, const Vector3& v2) {
    Vector3 v3(0, 0, 0);
    v3+=v1;
    v3+=v2;
    return v3;
}

Vector3 operator-(const Vector3& v1, const Vector3& v2) {
    Vector3 v3(0, 0, 0);
    v3-=v1;
    v3-=v2;
    return v3;
}

Vector3 operator*(const Vector3& v1, const float& f) {
    Vector3* v2 = new Vector3(v1);
    *v2 *=f;
    return *v2;
}


