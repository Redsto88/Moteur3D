#ifndef SPHERE3D_HPP
#define SPHERE3D_HPP

#include "volume3D.hpp"

class Sphere3D : public Volume3D
{
    private:
        std::vector<Quad> quads;
        SDL_Color color;
    
    public:
        Sphere3D(Sphere3D& _sphere);
        Sphere3D(Vector3& _center, const float _radius, const int _numSegments, SDL_Color _color);
        SDL_Color getColor() override;
        std::vector<Quad> getQuads() override;

};



#endif