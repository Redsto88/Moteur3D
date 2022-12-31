#include "triangle.hpp"


Triangle::Triangle(Vector3 _a, Vector3 _b, Vector3 _c, const uint32_t _color) {
    a = _a;
    b = _b;
    c = _c;
    color = _color;
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

uint32_t Triangle::getColor() const{
    return color;
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

Vector3 Triangle::getBarycentre(){
    
    float x = (a.getX() + c.getX()) / 2;
    float y = (a.getY() + c.getY()) / 2;
    float z = (a.getZ() + c.getZ()) / 2;
    return Vector3(x,y,z);
}


std::ostream& operator<<(std::ostream& st, Triangle& tri){
    st << tri.getA() << " // " << tri.getB() << " // " << tri.getC() << std::endl;
    return st;
}

