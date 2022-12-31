#include "quad.hpp"

Quad::Quad(const Triangle& _t1,const Triangle& _t2, const uint32_t _color)
{
    /*TODO : Les deux triangles doivent avoir deux points en commun (un côté en commun)*/
    t1 = _t1;
    t2 = _t2;
    color = _color;
}

Quad::Quad(const Vector3& _a, const Vector3& _b, const Vector3& _c, const Vector3& _d, const uint32_t _color)
{
    Triangle _t1(_a,_b,_c, _color);
    Triangle _t2(_c,_d,_a, _color);
    t1 = _t1;
    t2 = _t2;
    color = _color;
}

Triangle Quad::getT1() const
{
    return t1;
}

Triangle Quad::getT2() const
{
    return t2;
}

uint32_t Quad::getColor() const{
    return color;
}
std::vector<Vector3> Quad::getPoints() const
{
    std::vector<Vector3> points;
    points.push_back(t1.getA());
    points.push_back(t1.getB());
    points.push_back(t1.getC());
    points.push_back(t2.getA());
    return points;
}



