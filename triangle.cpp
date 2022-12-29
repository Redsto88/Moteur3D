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

void Triangle::setA(Vector3 _a){
    a = _a;
}
        
void Triangle::setB(Vector3 _b){
    b = _b;
}
       
void Triangle::setC(Vector3 _c){
    c = _c;
}


std::ostream& operator<<(std::ostream& st, Triangle& tri){
    st << tri.getA() << " // " << tri.getB() << " // " << tri.getC() << std::endl;
    return st;
}

