#ifndef quad3D_HPP
#define quad3D_HPP

#include "Triangle.hpp"
#include <vector>
#include "vector3.hpp"

class Quad3D
{
private:
    Triangle t1;
    Triangle t2;
public:
    Quad3D() = default;
    Quad3D(const Triangle& _t1,const Triangle& _t2);
    Quad3D(const Vector3& _a, const Vector3& _b, const Vector3& _c, const Vector3& _d);
    Triangle getT1() const;
    Triangle getT2() const;
    std::vector<Vector3> getPoints() const;
};





#endif