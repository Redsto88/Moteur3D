#ifndef quad3D_HPP
#define quad3D_HPP

#include "triangle3D.hpp"

class Quad3D
{
private:
    Triangle3D t1;
    Triangle3D t2;
public:
    Quad3D() = default;
    Quad3D(const Triangle3D& _t1,const Triangle3D& _t2);
    Triangle3D getT1() const;
    Triangle3D getT2() const;
};





#endif