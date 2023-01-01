#include "pave3D.hpp"

Pave3D::Pave3D(std::vector<Quad> _quads, SDL_Color _color)
{
    quads = _quads;
    color = _color;
}

Pave3D::Pave3D(Pave3D& _pave)
{
    quads = _pave.getQuads();
    color = _pave.getColor();
}

Pave3D::Pave3D(const Quad& _quad, float height, const SDL_Color _color)
{
    /*Les quatres points de la face frontale du pavé*/
    Vector3 leftBotomFront = _quad.getT1().getA();
    Vector3 leftTopFront = _quad.getT1().getB();
    Vector3 rightTopFront = _quad.getT1().getC();
    Vector3 rightBotomFront = _quad.getT2().getB();

    Vector3 prof(0,0,height);
    
    /*Les quatres points à l'arrière du pavé*/
    Vector3 rightTopBack = rightTopFront + prof;
    Vector3 rightBotomBack = rightBotomFront + prof;
    Vector3 leftTopBack = leftTopFront + prof;
    Vector3 leftBotomBack = leftBotomFront + prof;

    Pave3D(leftBotomFront,leftTopFront,rightTopFront,rightBotomFront,rightTopBack,rightBotomBack,leftTopBack,leftBotomBack,_color);
}

Pave3D::Pave3D(const Vector3& leftBotomFront,
                const Vector3& leftTopFront,
                const Vector3& rightTopFront,
                const Vector3& rightBotomFront,
                const Vector3& rightTopBack,
                const Vector3& rightBotomBack,
                const Vector3& leftTopBack,
                const Vector3& leftBotomBack,
                const SDL_Color _color)
{
    color = _color;

    Triangle triFront1(rightTopFront,leftTopFront,leftBotomFront, color);
    Triangle triFront2(leftBotomFront,rightBotomFront,rightTopFront, color);
    Triangle triRight1(rightTopBack,rightTopFront,rightBotomFront, color);
    Triangle triRight2(rightBotomFront,rightBotomBack,rightTopBack, color);
    Triangle triBack1(leftTopBack,rightTopBack,rightBotomBack, color);
    Triangle triBack2(rightBotomBack,leftBotomBack,leftTopBack, color);
    Triangle triLeft1(leftTopFront,leftTopBack,leftBotomBack, color);
    Triangle triLeft2(leftBotomBack,leftBotomFront,leftTopFront, color);
    Triangle triTop1(leftTopFront,rightTopFront,rightTopBack, color);
    Triangle triTop2(rightTopBack,leftTopBack,leftTopFront, color);
    Triangle triBotom1(leftBotomFront, leftBotomBack,rightBotomBack, color);
    Triangle triBotom2(rightBotomBack, rightBotomFront,leftBotomFront, color);

    Quad front(triFront1,triFront2,color);
    Quad rigth(triRight1,triRight2,color);
    Quad back(triBack1,triBack2,color);
    Quad left(triLeft1,triLeft2,color);
    Quad top(triTop1,triTop2,color);
    Quad botom(triBotom1,triBotom2,color);

    quads = std::vector<Quad>();
    quads.push_back(front);
    quads.push_back(rigth);
    quads.push_back(back);
    quads.push_back(left);
    quads.push_back(top);
    quads.push_back(botom);
}

std::vector<Quad> Pave3D::getQuads() 
{
    //std::cout << "Pave3D::getQuads()" << std::endl;
    //std::cout << "quads.size() = " << quads.size() << std::endl;
    return quads;
}

SDL_Color Pave3D::getColor(){
    return color;
}





