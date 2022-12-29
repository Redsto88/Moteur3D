#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include "matrix4.hpp"

class Vector3 {

    private : 
        float x;
        float y;
        float z;
    
    public :
        Vector3(float x = 0, float y = 0, float z = 0);
        float getX() const;
        float getY() const;
        float getZ() const;
        Vector3 setX(const float x);
        Vector3 setY(const float y);
        Vector3 setZ(const float z);

        void operator+=(const Vector3& v);
        void operator-=(const Vector3& v);
        void operator*=(const float& f);
        void operator/=(const float& f);

        friend Vector3 operator+(const Vector3& v1, const Vector3& v2);
        friend Vector3 operator-(const Vector3& v1, const Vector3& v2);
        friend Vector3 operator*(const Vector3& v1, const float& f);
        friend Vector3 operator*(const float& f, const Vector3& v1);

        Vector3 multiplyVector3ByMatrix4(Vector3 vOutput, const Matrix4& m);
};

std::ostream& operator<<(std::ostream& st, Vector3 v);


Vector3 operator+(const Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3& v1, const Vector3& v2);
Vector3 operator*(const Vector3& v1, const float& f);
Vector3 operator*(const float& f, const Vector3& v1);
Vector3 operator/(const Vector3& v1, const float& f);
Vector3 operator/(const float& f, const Vector3& v1);

Vector3 planeNormal(const Vector3& v1, const Vector3& v2, const Vector3& v3);





#endif