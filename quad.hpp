#ifndef Quad_HPP
#define Quad_HPP

#include <vector>
#include "Triangle.hpp"

class Quad
{
private:
    Triangle t1;
    Triangle t2;
    SDL_Color color;
public:
    Quad() = default;
    Quad(const Triangle& _t1,const Triangle& _t2, const SDL_Color _color);
    //les vecteurs doivent être donné dans le sens suivant lorsque la normale du quad pointe vers nous
        //bas_droite
        //haut_droite
        //haut_gauche
        //bas_gauche
    Quad(const Vector3& _a, const Vector3& _b, const Vector3& _c, const Vector3& _d, const SDL_Color _color); 
    Triangle getT1() const;
    Triangle getT2() const;
    SDL_Color getColor() const;
};





#endif