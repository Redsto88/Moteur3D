#include "matrix4.hpp"


Matrix4::Matrix4()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            m[i][j] = 0.0f;
        }
    }
}

Matrix4::Matrix4(float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33)
{
    m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
    m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
    m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
    m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}

float& Matrix4::operator[](std::pair<int, int> index)
{
    return m[index.first][index.second];
}

const float& Matrix4::operator[](std::pair<int, int> index) const
{
    return m[index.first][index.second];
}

std::ostream& operator<<(std::ostream& st, Matrix4& m)
{
    st << m[{0,0}] << "; " << m[{0,1}] << "; " << m[{0,2}] << "; " << m[{0,3}] << std::endl
    << m[{1,0}] << "; " << m[{1,1}] << "; " << m[{1,2}] << "; " << m[{1,3}] << std::endl
    << m[{2,0}] << "; " << m[{2,1}] << "; " << m[{2,2}] << "; " << m[{2,3}] << std::endl
    << m[{3,0}] << "; " << m[{3,1}] << "; " << m[{3,2}] << "; " << m[{3,3}] << std::endl << std::endl;
    return st;
}



Matrix4 Matrix4::inverse(){
    Matrix4 result;
    result[{0,0}] = m[0][0] ; result[{0,1}] = m[1][0] ; result[{0,2}] = m[2][0] ; result[{0,3}] = 0.0f;
    result[{1,0}] = m[0][1] ; result[{1,1}] = m[1][1] ; result[{1,2}] = m[2][1] ; result[{1,3}] = 0.0f;
    result[{2,0}] = m[0][2] ; result[{2,1}] = m[1][2] ; result[{2,2}] = m[2][2] ; result[{2,3}] = 0.0f;
    result[{3,0}] = -(m[3][0] * result[{0,0}] + m[3][1] * result[{1,0}] + m[3][2] * result[{2,0}]);
    result[{3,1}] = -(m[3][0] * result[{0,1}] + m[3][1] * result[{1,1}] + m[3][2] * result[{2,1}]);
    result[{3,2}] = -(m[3][0] * result[{0,2}] + m[3][1] * result[{1,2}] + m[3][2] * result[{2,2}]);
    result[{3,3}] = 1.0f;
    return result;
}

Matrix4 Matrix4::operator*= (const Matrix4& m2)
{
    Matrix4 result;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            result[{i,j}] = m[i][0] * m2[{0,j}] + m[i][1] * m2[{1,j}] + m[i][2] * m2[{2,j}] + m[i][3]* m2[{3,j}];
        }
    }
    return result;
}

Matrix4 operator*(const Matrix4& m1, const Matrix4& m2)
{
    Matrix4 result = m1;
    result *= m2;
    return result;
}