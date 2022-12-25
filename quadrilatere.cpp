#include "quadrilatere.hpp"

quadrilatere::quadrilatere(Triangle _t1, Triangle _t2)
{
    t1 = _t1;
    t2 = _t2;
}

Triangle quadrilatere::getT1() const
{
    return t1;
}

Triangle quadrilatere::getT2() const
{
    return t2;
}



