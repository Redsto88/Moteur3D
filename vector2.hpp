#ifndef VECTOR2_HPP
#define VECTOR2_HPP



class Vector2 {

    private : 
        double x;
        double y;
    
    public :
        Vector2(double x = 0, double y = 0);
        double getX() const;
        double getY() const;

        void operator+=(const Vector2& v);
        void operator-=(const Vector2& v);
};



#endif