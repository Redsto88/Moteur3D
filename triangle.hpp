#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "vector3.hpp"

class Triangle{
    private:
        Vector3 a;
        Vector3 b;
        Vector3 c;
        SDL_Color color;

    public:
        Triangle();
        Triangle(Vector3& a,Vector3& b,Vector3& c, const SDL_Color& _color);
        Triangle(const Triangle& tri);
        Vector3& getA();
        Vector3& getB();
        Vector3& getC();
        SDL_Color& getColor();
        void setA(const Vector3& _a);
        void setB(const Vector3& _b);
        void setC(const Vector3& _c);
        void setColor(const SDL_Color& _color);
        Vector3 getBarycentre();
        Triangle multiplyByMatrix(const Matrix4& mat);
        void operator+= (const Vector3& vec);
        void operator*= (float scalar);
        void inverseXY();
        void scaleToViewAndWindow(int window_width,int window_height);
};

std::ostream& operator<<(std::ostream& st, Triangle& tri);


#endif