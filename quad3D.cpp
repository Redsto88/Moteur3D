#include "quad3D.hpp"

Quad3D::Quad3D(const Triangle& _t1,const Triangle& _t2)
{
    /*TODO : Les deux triangles doivent avoir deux points en commun (un côté en commun)*/
    t1 = _t1;
    t2 = _t2;
}

Quad3D::Quad3D(const Vector3& _a, const Vector3& _b, const Vector3& _c, const Vector3& _d)
{
    Triangle _t1(_a,_b,_c);
    Triangle _t2(_d,_b,_c);
    t1 = _t1;
    t2 = _t2;
}

Triangle Quad3D::getT1() const
{
    return t1;
}

Triangle Quad3D::getT2() const
{
    return t2;
}

std::vector<Vector3> Quad3D::getPoints() const
{
    std::vector<Vector3> points;
    points.push_back(t1.getA());
    points.push_back(t1.getB());
    points.push_back(t1.getC());
    points.push_back(t2.getA());
    return points;
}



