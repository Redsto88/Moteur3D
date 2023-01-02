#include "quad.hpp"


Quad::Quad(Triangle& _t1,Triangle& _t2, SDL_Color& _color)
{
    /*TODO : Les deux triangles doivent avoir deux points en commun (un côté en commun)*/
    t1 = _t1;
    t2 = _t2;
    color = _color;
}

Quad::Quad(Vector3& _a, Vector3& _b, Vector3& _c, Vector3& _d, SDL_Color& _color)
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

SDL_Color Quad::getColor() const{
    return color;
}