#ifndef PAVE3D_HPP
#define PAVE3D_HPP

#include <iostream>
#include <vector>

#include "quad3D.hpp"
#include "volume3D.hpp"

class Pave3D : public Volume3D
{
    private:
        std::vector<Quad3D> quads;

    public:

        Pave3D(std::vector<Quad3D> _quads);
        Pave3D(Pave3D& _pave);
        Pave3D(const Quad3D& _quad, float height);
        std::vector<Quad3D> getQuads() override;




};



#endif