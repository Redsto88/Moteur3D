#include "triangle.hpp"


Triangle::Triangle() {
    a = Vector3(0,0,0);
    b = Vector3(0,0,0);
    c = Vector3(0,0,0);
}


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

//La normale du triangle pointe vers "l'oeil" si on le lit A->B->C dans le sens des aiguilles d'une montre
bool Triangle::isVisible(){
    if(c.getX() < b.getX() 
            && a.getY() < b.getY())
    {
        return false;
    }
    else if(c.getX() > b.getX()
            && a.getY() > b.getY())
    {
        return false;
    }

    return true;
}


std::ostream& operator<<(std::ostream& st, Triangle& tri){
    st << tri.getA() << " // " << tri.getB() << " // " << tri.getC() << std::endl;
    return st;
}

