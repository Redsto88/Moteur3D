#ifndef Quad_HPP
#define Quad_HPP

#include "Triangle.hpp"
#include <vector>
#include "vector3.hpp"

class Quad
{
private:
    Triangle t1;
    Triangle t2;
    uint32_t color;
public:
    Quad() = default;
    Quad(const Triangle& _t1,const Triangle& _t2, const uint32_t _color);
    //les vecteurs doivent être donné dans le sens suivant lorsque la normale du quad pointe vers nous
        //bas_gauche
        //haut_gauche
        //haut_droite
        //bas_droite
    Quad(const Vector3& _a, const Vector3& _b, const Vector3& _c, const Vector3& _d, const uint32_t _color); 
    Triangle getT1() const;
    Triangle getT2() const;
    uint32_t getColor() const;
    std::vector<Vector3> getPoints() const;
};





#endif