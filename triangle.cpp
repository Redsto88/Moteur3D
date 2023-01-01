#include "triangle.hpp"


Triangle::Triangle() {
    a = Vector3(0,0,0);
    b = Vector3(0,0,0);
    c = Vector3(0,0,0);
}


Triangle::Triangle(Vector3 _a, Vector3 _b, Vector3 _c, const SDL_Color _color) {
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

SDL_Color Triangle::getColor() const{
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

void Triangle::setColor(SDL_Color _color){
    color = _color;
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

