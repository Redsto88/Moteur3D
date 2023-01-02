#ifndef PAVE3D_HPP
#define PAVE3D_HPP

#include "volume3D.hpp"

class Pave3D : public Volume3D
{
    private:
        std::vector<Quad> quads;
        SDL_Color color;

    public:
        Pave3D(Pave3D& _pave);
        Pave3D( Vector3& leftBotomForward,
                Vector3& leftTopForward,
                Vector3& rightTopForward,
                Vector3& rightBotomForward,
                Vector3& rightTopBackward,
                Vector3& rightBotomBackward,
                Vector3& leftTopBackward,
                Vector3& leftBotomBackward,
                SDL_Color& _color);
        std::vector<Quad> getQuads() override;
        SDL_Color getColor() override;
};





#endif