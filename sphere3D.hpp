#ifndef SPHERE3D_HPP
#define SPHERE3D_HPP

#include "volume3D.hpp"

class Sphere3D : public Volume3D
{
    private:
        Vector3 center;
        float radius;
        std::vector<Quad> quads;
        //std::vector<Triangle> triangles;
    public:

        Sphere3D(Sphere3D& _sphere);
        Sphere3D(Vector3& _center, const float _radius, const int numSegments);
        Vector3 getCenter();
        float getRadius();
        std::vector<Quad> getQuads() override;

};



#endif