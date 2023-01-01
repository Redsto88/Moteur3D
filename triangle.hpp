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
        Triangle(Vector3 a, Vector3 b, Vector3 c, const SDL_Color _color);
        Vector3 getA() const;
        Vector3 getB() const;
        Vector3 getC() const;
        SDL_Color getColor() const;
        void setA(Vector3 _a);
        void setB(Vector3 _b);
        void setC(Vector3 _c);
        void setColor(SDL_Color _color);
        Vector3 getBarycentre();
};

std::ostream& operator<<(std::ostream& st, Triangle& tri);


#endif