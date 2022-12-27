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

void Vector3::setX(const float _x)
{
    x=_x;
}
        
void Vector3::setY(const float _y)
{
    y=_y;
}
        
void Vector3::setZ(const float _z)
{
    z=_z;
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

Vector3 operator*(const float& f, const Vector3& v1) {
    Vector3* v2 = new Vector3(v1);
    *v2 *=f;
    return *v2;
}

Vector3 operator/(const Vector3& v1, const float& f) {
    Vector3* v2 = new Vector3(v1);
    *v2 /=f;
    return *v2;
}

Vector3 operator/(const float& f, const Vector3& v1) {
    Vector3* v2 = new Vector3(v1);
    *v2 /=f;
    return *v2;
}

Vector3 planeNormal(const Vector3& v1, const Vector3& v2, const Vector3& v3) {
    Vector3 v4 = v2 - v1;
    Vector3 v5 = v3 - v1;
    Vector3 v6(v4.getY()*v5.getZ() - v4.getZ()*v5.getY(), v4.getZ()*v5.getX() - v4.getX()*v5.getZ(), v4.getX()*v5.getY() - v4.getY()*v5.getX());
    return v6;
}


