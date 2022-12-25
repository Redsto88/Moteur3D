#include "triangle3D.hpp"


Triangle3D::Triangle3D(Vector3 _a, Vector3 _b, Vector3 _c) {
    a = _a;
    b = _b;
    c = _c;
}


Vector3 Triangle3D::getA() const {
    return a;
}

Vector3 Triangle3D::getB() const {
    return b;
}

Vector3 Triangle3D::getC() const {
    return c;
}

