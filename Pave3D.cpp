#include "pave3D.hpp"


Pave3D::Pave3D(Pave3D& _pave){
    quads = _pave.getQuads();
    color = _pave.getColor();
}

Pave3D::Pave3D( Vector3& leftBotomFront,
                Vector3& leftTopFront,
                Vector3& rightTopFront,
                Vector3& rightBotomFront,
                Vector3& rightTopBack,
                Vector3& rightBotomBack,
                Vector3& leftTopBack,
                Vector3& leftBotomBack,
                SDL_Color& _color){
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

std::vector<Quad> Pave3D::getQuads() {
    return quads;
}

SDL_Color Pave3D::getColor(){
    return color;
}





