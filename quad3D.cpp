#include "quad3D.hpp"

Quad3D::Quad3D(const Triangle3D& _t1,const Triangle3D& _t2)
{
    /*TODO : Les deux triangles doivent avoir deux points en commun (un côté en commun)*/
    t1 = _t1;
    t2 = _t2;
}

Quad3D::Quad3D(const Vector3& _a, const Vector3& _b, const Vector3& _c, const Vector3& _d)
{
    Triangle3D _t1(_a,_b,_c);
    Triangle3D _t2(_d,_b,_c);
    t1 = _t1;
    t2 = _t2;
}

Triangle3D Quad3D::getT1() const
{
    return t1;
}

Triangle3D Quad3D::getT2() const
{
    return t2;
}



