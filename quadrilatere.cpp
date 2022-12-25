#include "quadrilatere.hpp"

quadrilatere::quadrilatere(Vector3 _a, Vector3 _b, Vector3 _c, Vector3 _d) {
    a = _a;
    b = _b;
    c = _c;
    d = _d;
}


Vector3 quadrilatere::getA() const {
    return a;
}

Vector3 quadrilatere::getB() const {
    return b;
}

Vector3 quadrilatere::getC() const {
    return c;
}

Vector3 quadrilatere::getD() const {
    return d;
}

