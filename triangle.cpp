#include "triangle.hpp"

Triangle::Triangle(Vector3 _a, Vector3 _b, Vector3 _c) {
    a = _a;
    b = _b;
    c = _c;
}


Vector3 Triangle::getA() const {
    return a;
}

Vector3 Triangle::getB() const {
    return b;
}

Vector3 Triangle::getC() const {
    return c;
}

