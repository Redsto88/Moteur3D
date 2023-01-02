#include "triangle.hpp"


Triangle::Triangle() {
    a = Vector3(0,0,0);
    b = Vector3(0,0,0);
    c = Vector3(0,0,0);
}


Triangle::Triangle(Vector3& _a, Vector3& _b, Vector3& _c, const SDL_Color& _color) {
    a = _a;
    b = _b;
    c = _c;
    color = _color;
}

Triangle::Triangle(const Triangle& tri) {
    Vector3 _a(tri.a.getX(), tri.a.getY(), tri.a.getZ());
    Vector3 _b(tri.b.getX(), tri.b.getY(), tri.b.getZ());
    Vector3 _c(tri.c.getX(), tri.c.getY(), tri.c.getZ());
    a = _a;
    b = _b;
    c = _c;
    color = tri.color;
}


Vector3& Triangle::getA() {
    return a;
}

Vector3& Triangle::getB(){
    return b;
}

Vector3& Triangle::getC() {
    return c;
}

SDL_Color& Triangle::getColor() {
    return color;
}


void Triangle::setA(const Vector3& _a){
    a = _a;
}
        
void Triangle::setB(const Vector3& _b){
    b = _b;
}
       
void Triangle::setC(const Vector3& _c){
    c = _c;
}

void Triangle::setColor(const SDL_Color& _color){
    color = _color;
}

Vector3 Triangle::getCenterThirdSide(){
    
    float x = (a.getX() + c.getX()) / 2;
    float y = (a.getY() + c.getY()) / 2;
    float z = (a.getZ() + c.getZ()) / 2;
    return Vector3(x,y,z);
}

void Triangle::operator*= (float scalar){
    a *= scalar;
    b *= scalar;
    c *= scalar;
}

void Triangle::inverseXY(){
    a.inverseXY();
    b.inverseXY();
    c.inverseXY();
}

Triangle Triangle::multiplyByMatrix(const Matrix4& mat){
    a = a.multiplyVector3ByMatrix4(mat);
    b = b.multiplyVector3ByMatrix4(mat);
    c = c.multiplyVector3ByMatrix4(mat);
    return *this;
}

void Triangle::operator+= (const Vector3& vec){
    a += vec;
    b += vec;
    c += vec;
}

std::ostream& operator<<(std::ostream& st, Triangle& tri){
    st << tri.getA() << " // " << tri.getB() << " // " << tri.getC() << std::endl;
    return st;
}

void Triangle::scaleToViewAndWindow(int window_width,int window_height){
    a+= Vector3(1,1,0);
    b+= Vector3(1,1,0);
    c+= Vector3(1,1,0);
    a = a * Vector3(0.5*((float) window_width),0.5*((float)window_height),1);
    b = b * Vector3(0.5*((float) window_width),0.5*((float)window_height),1);
    c = c * Vector3(0.5*((float) window_width),0.5*((float)window_height),1);
}

