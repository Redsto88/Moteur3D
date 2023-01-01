#ifndef PAVE3D_HPP
#define PAVE3D_HPP

#include "volume3D.hpp"

class Pave3D : public Volume3D
{
    private:
        std::vector<Quad> quads;
        SDL_Color color;

    public:

        Pave3D(std::vector<Quad> _quads, SDL_Color _color);
        Pave3D(Pave3D& _pave);
        Pave3D(const Quad& _quad, float height, const SDL_Color _color);
        Pave3D(const Vector3& leftBotomForward,
                const Vector3& leftTopForward,
                const Vector3& rightTopForward,
                const Vector3& rightBotomForward,
                const Vector3& rightTopBackward,
                const Vector3& rightBotomBackward,
                const Vector3& leftTopBackward,
                const Vector3& leftBotomBackward,
                const SDL_Color _color);
        std::vector<Quad> getQuads() override;
        SDL_Color getColor() override;
};





#endif