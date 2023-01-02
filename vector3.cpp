#include "vector3.hpp"


Vector3::Vector3(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;
    w = 1;
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

float Vector3::getW() const {
    return w;
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

Vector3 Vector3::setW(const float _w)
{
    w=_w;
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

Vector3 Vector3::multiplyVector3ByMatrix4(const Matrix4& m) 
{
    Vector3 result;
    // x = (x * m[{0,0}] + y * m[{1,0}] + z * m[{2,0}] + w*m[{3,0}]);
    // y = (x * m[{0,1}] + y * m[{1,1}] + z * m[{2,1}] + w*m[{3,1}]);
    // z = (x * m[{0,2}] + y * m[{1,2}] + z * m[{2,2}] + w*m[{3,2}]);
    // w = (x * m[{0,3}] + y * m[{1,3}] + z * m[{2,3}] + w*m[{3,3}]);
    result.setX(x * m[{0,0}] + y * m[{1,0}] + z * m[{2,0}] + w*m[{3,0}]);
    result.setY(x * m[{0,1}] + y * m[{1,1}] + z * m[{2,1}] + w*m[{3,1}]);
    result.setZ(x * m[{0,2}] + y * m[{1,2}] + z * m[{2,2}] + w*m[{3,2}]);
    result.setW(x * m[{0,3}] + y * m[{1,3}] + z * m[{2,3}] + w*m[{3,3}]);
    return result;
}

void Vector3::inverseXY() {
    x*=-1;
    y*=-1;
}

Vector3 Vector3::multiplyVector3ByMatrix4(Vector3 vOutput, const Matrix4& m) 
{
    vOutput.setX(x * m[{0,0}] + y * m[{1,0}] + z * m[{2,0}] + w*m[{3,0}]);
    vOutput.setY(x * m[{0,1}] + y * m[{1,1}] + z * m[{2,1}] + w*m[{3,1}]);
    vOutput.setZ(x * m[{0,2}] + y * m[{1,2}] + z * m[{2,2}] + w*m[{3,2}]);
    vOutput.setW(x * m[{0,3}] + y * m[{1,3}] + z * m[{2,3}] + w*m[{3,3}]);


    return vOutput;
}

void Vector3::normalize() {
    float length = std::sqrt(x*x + y*y + z*z);
    if (length != 0) {
        x /= length;
        y /= length;
        z /= length;
    }
}

float Vector3::dotProduct(const Vector3& v) const {
    return x*v.x + y*v.y + z*v.z;
}

Vector3 Vector3::crossProduct(const Vector3& v) const {
    return Vector3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}


float Vector3::magnitude(){
    return sqrt(x*x + y*y + z*z);
}

std::ostream& operator<<(std::ostream& st, Vector3 v){
    st << "(" << v.getX() << "; " << v.getY() << "; " << v.getZ() << "; " << v.getW() <<")" << std::endl;
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
    v3+=v1;
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

Vector3 operator*(const Vector3& v1, const Vector3& v2) {
    Vector3 v3(0, 0, 0);
    v3.setX(v1.getX()*v2.getX());
    v3.setY(v1.getY()*v2.getY());
    v3.setZ(v1.getZ()*v2.getZ());
    return v3;
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

Matrix4 Matrix_camera (Vector3& pos, Vector3& cible, Vector3& up)
{

    //calcul de la direction dans laquelle on regarde
    Vector3 forward = cible - pos;
    forward.normalize();

    Vector3 up2 = forward*up.dotProduct(forward);
    
    up2 = up - up2;
    up2.normalize();

    Vector3 right = CrossProduct(up2,forward);


    Matrix4 result;
    result[{0,0}] = right.getX(); result[{0,1}] = right.getY(); result[{0,2}] = right.getZ(); result[{0,3}] = 0.0f;
    result[{1,0}] = up2.getX(); result[{1,1}] = up2.getY(); result[{1,2}] = up2.getZ(); result[{1,3}] = 0.0f;
    result[{2,0}] = forward.getX(); result[{2,1}] = forward.getY(); result[{2,2}] = forward.getZ(); result[{2,3}] = 0.0f;
    result[{3,0}] = pos.getX(); result[{3,1}] = pos.getY(); result[{3,2}] = pos.getZ(); result[{3,3}] = 1.0f;

    return result;
}

Vector3 CrossProduct(const Vector3& v1, const Vector3& v2) {
    return Vector3(v1.getY()*v2.getZ() - v1.getZ()*v2.getY(), v1.getZ()*v2.getX() - v1.getX()*v2.getZ(), v1.getX()*v2.getY() - v1.getY()*v2.getX());
}
