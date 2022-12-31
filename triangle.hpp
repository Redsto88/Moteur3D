#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "vector3.hpp"



class Triangle{
    private:
        Vector3 a;
        Vector3 b;
        Vector3 c;
        uint32_t color;

    public:
        Triangle() = default;
        Triangle(Vector3 a, Vector3 b, Vector3 c, const uint32_t _color);
        Vector3 getA() const;
        Vector3 getB() const;
        Vector3 getC() const;
        uint32_t getColor() const;
        void setA(Vector3 _a);
        void setB(Vector3 _b);
        void setC(Vector3 _c);
        bool isVisible(); //true si la normale du triangle pointe vers "l'oeil". Dans ce cas il doit être affiché 
                          // ne sert qu'une fois le triangle projeté sur l'écran
        Vector3 getBarycentre();
};

std::ostream& operator<<(std::ostream& st, Triangle& tri);


#endif