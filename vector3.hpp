#ifndef VECTOR2_HPP
#define VECTOR2_HPP



class Vector3 {

    private : 
        float x;
        float y;
        float z;
    
    public :
        Vector3(float x = 0, float y = 0, float z = 0);
        float getX() const;
        float getY() const;
        float getZ() const;

        void operator+=(const Vector3& v);
        void operator-=(const Vector3& v);
};



#endif