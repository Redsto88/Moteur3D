#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "vector3.hpp"
#include <cmath>


class Triangle{
    private:
        Vector3 a;
        Vector3 b;
        Vector3 c;
    public:
        Triangle() = default;
        Triangle(Vector3 a, Vector3 b, Vector3 c);
        Vector3 getA() const;
        Vector3 getB() const;
        Vector3 getC() const;
        void setA(Vector3 _a);
        void setB(Vector3 _b);
        void setC(Vector3 _c);
};

std::ostream& operator<<(std::ostream& st, Triangle& tri);


#endif