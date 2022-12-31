#include "pave3D.hpp"

Pave3D::Pave3D(std::vector<Quad> _quads, uint32_t _color)
{
    quads = _quads;
    color = _color;
}

Pave3D::Pave3D(Pave3D& _pave)
{
    quads = _pave.getQuads();
    color = _pave.getColor();
}

Pave3D::Pave3D(const Quad& _quad, float height, const uint32_t _color)
{
    color = _color;

    /*Les quatres points de la base du quadrilatère*/
    Vector3 DownA = _quad.getT1().getA();
    Vector3 DownB = _quad.getT1().getB();
    Vector3 DownC = _quad.getT1().getC();
    Vector3 DownD = _quad.getT2().getA();
    Vector3 normal = planeNormal(DownA, DownB, DownC);//normale du plan de la base

    /*Les quatres points du haut du quadrilatère*/
    Vector3 UpA = DownA + normal * height;
    Vector3 UpB = DownB + normal * height;
    Vector3 UpC = DownC + normal * height;
    Vector3 UpD = DownD + normal * height;

    /*les triangles du haut*/
    Triangle t1(UpA, UpB, UpC, color);
    Triangle t2(UpD, UpB, UpC, color);
    Quad q1(t1,t2,color);

    /*Les triangles des côtés*/
    Triangle t3(DownA, DownB, UpA, color);
    Triangle t4(UpB, DownB, UpA, color);
    Quad q2(t3,t4,color);

    Triangle t5(DownB, DownC, UpB, color);
    Triangle t6(UpC, DownC, UpB, color);
    Quad q3(t5,t6,color);

    Triangle t7(DownC, DownD, UpC, color);
    Triangle t8(UpD, DownD, UpC, color);
    Quad q4(t7,t8,color);

    Triangle t9(DownD, DownA, UpD, color);
    Triangle t10(UpA, DownA, UpD, color);
    Quad q5(t9,t10,color);
    quads = std::vector<Quad>();
    quads.push_back(_quad);
    quads.push_back(q1);
    quads.push_back(q2);
    quads.push_back(q3);
    quads.push_back(q4);
    quads.push_back(q5);
}

Pave3D::Pave3D(const Vector3& leftBotomFront,
                const Vector3& leftTopFront,
                const Vector3& rightTopFront,
                const Vector3& rightBotomFront,
                const Vector3& rightTopBack,
                const Vector3& rightBotomBack,
                const Vector3& leftTopBack,
                const Vector3& leftBotomBack,
                const uint32_t _color)
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

uint32_t Pave3D::getColor(){
    return color;
}





