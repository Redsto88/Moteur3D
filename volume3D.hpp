#ifndef VOL3D_HPP
#define VOL3D_HPP

#include "quad.hpp"

class Volume3D
{
    private:
        std::vector<Quad> quads;
        SDL_Color color;

    public:
        Volume3D() = default;
        ~Volume3D() = default;

        virtual SDL_Color getColor()
        {
            std::cout << "WRONG" << std::endl;
            std::cout << "couleur = " << color.a << "; " << color.r << "; " << color.g << "; " << color.b << std::endl;
            return color;
        };
        virtual std::vector<Quad> getQuads()
        {
            std::cout << "WRONG" << std::endl;
            std::cout << "quads.size() = " << quads.size() << std::endl;
            return quads;
        };
};

#endif