#ifndef VECTOR2_HPP
#define VECTOR2_HPP



class Vector3 {

    private : 
        double x;
        double y;
        double z;
    
    public :
        Vector3(double x = 0, double y = 0, double z = 0);
        double getX() const;
        double getY() const;
        double getZ() const;

        void operator+=(const Vector3& v);
        void operator-=(const Vector3& v);
};



#endif