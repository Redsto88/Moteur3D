#ifndef VOL3D_HPP
#define VOL3D_HPP

#include <vector>

#include "quad3D.hpp"

class Volume3D
{
    private:
        std::vector<Quad3D> quads;
};

#endif