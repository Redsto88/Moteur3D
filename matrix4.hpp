#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include <iostream>

class Matrix4
{
    private :
        float m[4][4];
    
    public:
        Matrix4();
        Matrix4(float m00, float m01, float m02, float m03,
                float m10, float m11, float m12, float m13,
                float m20, float m21, float m22, float m23,
                float m30, float m31, float m32, float m33);
        float& operator[](std::pair<int, int> index);
        const float& operator[](std::pair<int, int> index) const;
        Matrix4 inverse();
        Matrix4 operator *= (const Matrix4& m);
        friend Matrix4 operator*(const Matrix4& m, const Matrix4& m2);
        //Vector3& operator*(const Vector3& v);
};


std::ostream& operator<<(std::ostream& st, Matrix4& m);
Matrix4 operator*(const Matrix4& m1, const Matrix4& m2);


#endif