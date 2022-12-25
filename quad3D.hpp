#ifndef quad3D_HPP
#define quad3D_HPP

#include "triangle3D.hpp"
#include <vector>
#include "vector3.hpp"

class Quad3D
{
private:
    Triangle3D t1;
    Triangle3D t2;
public:
    Quad3D() = default;
    Quad3D(const Triangle3D& _t1,const Triangle3D& _t2);
    Quad3D(const Vector3& _a, const Vector3& _b, const Vector3& _c, const Vector3& _d);
    Triangle3D getT1() const;
    Triangle3D getT2() const;
    std::vector<Vector3> getPoints() const;
};





#endif