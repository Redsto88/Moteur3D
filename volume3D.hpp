#ifndef VOL3D_HPP
#define VOL3D_HPP

#include <vector>
#include <iostream>

#include "quad3D.hpp"

class Volume3D
{
    private:
        std::vector<Quad3D> quads;

    public:
        Volume3D() = default;
        ~Volume3D() = default;

        virtual std::vector<Quad3D> getQuads()
        {
            std::cout << "WRONG" << std::endl;
            std::cout << "quads.size() = " << quads.size() << std::endl;
            return quads;
        };
};

#endif