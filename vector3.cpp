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

Vector3 Vector3::setX(const float _x)
{
    x=_x;
    return *this;
}
        
Vector3 Vector3::setY(const float _y)
{
    y=_y;
    return *this;
}
        
Vector3 Vector3::setZ(const float _z)
{
    z=_z;
    return *this;
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

Vector3 Vector3::multiplyVector3ByMatrix4(Vector3& vOutput, const Matrix4& m) 
{
    vOutput.setX(x * m[{0,0}] + y * m[{1,0}] + z * m[{2,0}] + m[{3,0}]);
    vOutput.setY(x * m[{0,1}] + y * m[{1,1}] + z * m[{2,1}] + m[{3,1}]);
    vOutput.setZ(x * m[{0,2}] + y * m[{1,2}] + z * m[{2,2}] + m[{3,2}]);
    float w = x * m[{0,3}] + y * m[{1,3}] + z * m[{2,3}] + m[{3,3}];
    
    if (w != 0.0f)
    {
        vOutput /= w;
    }

    return vOutput;
}

std::ostream& operator<<(std::ostream& st, Vector3 v){
    st << "(" << v.getX() << "; " << v.getY() << "; " << v.getZ() << ")" << std::endl;
    return st;
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


