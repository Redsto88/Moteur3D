#ifndef VOL3D_HPP
#define VOL3D_HPP

#include <vector>
#include <iostream>

#include "Quad.hpp"

class Volume3D
{
    private:
        std::vector<Quad> quads;
        uint16_t color;

    public:
        Volume3D() = default;
        ~Volume3D() = default;

        virtual uint32_t getColor()
        {
            std::cout << "WRONG" << std::endl;
            std::cout << "couleur = " << color << std::endl;
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