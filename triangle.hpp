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
        Triangle(Vector3 a, Vector3 b, Vector3 c);
        Triangle(Triangle const& t);
        Vector3 getA() const;
        Vector3 getB() const;
        Vector3 getC() const;
};




#endif