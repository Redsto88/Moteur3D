#ifndef PAVE3D_HPP
#define PAVE3D_HPP

#include <iostream>
#include <vector>

#include "quad3D.hpp"

class Pave3D
{
    private:
        std::vector<Quad3D> quads;

    public:

        Pave3D() = default;
        Pave3D(std::vector<Quad3D> _quads);
        Pave3D(const Pave3D& _pave);
        Pave3D(const Quad3D& _quad, float height);
        std::vector<Quad3D> getQuads() const;




};



#endif