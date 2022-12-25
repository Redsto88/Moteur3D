#ifndef QUADRILATERE_HPP
#define QUADRILATERE_HPP

#include "triangle.hpp"

class quadrilatere
{
private:
    Triangle t1;
    Triangle t2;
public:
    quadrilatere(Triangle t1, Triangle t2);
    Triangle getT1() const;
    Triangle getT2() const;
};





#endif