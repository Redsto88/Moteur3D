#ifndef VECTOR2_HPP
#define VECTOR2_HPP



class Vector2 {

    private : 
        int x;
        int y;
    
    public :
        Vector2(int x = 0, int y = 0);
        int getX() const;
        int getY() const;

        void operator+=(const Vector2& v);
        void operator-=(const Vector2& v);
};



#endif