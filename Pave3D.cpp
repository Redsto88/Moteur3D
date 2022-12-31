#include "pave3D.hpp"

Pave3D::Pave3D(std::vector<Quad> _quads)
{
    quads = _quads;
}

Pave3D::Pave3D(Pave3D& _pave)
{
    quads = _pave.getQuads();
}

Pave3D::Pave3D(const Quad& _quad, float height)
{
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
    Triangle t1(UpA, UpB, UpC);
    Triangle t2(UpD, UpB, UpC);
    Quad q1(t1,t2);

    /*Les triangles des côtés*/
    Triangle t3(DownA, DownB, UpA);
    Triangle t4(UpB, DownB, UpA);
    Quad q2(t3,t4);

    Triangle t5(DownB, DownC, UpB);
    Triangle t6(UpC, DownC, UpB);
    Quad q3(t5,t6);

    Triangle t7(DownC, DownD, UpC);
    Triangle t8(UpD, DownD, UpC);
    Quad q4(t7,t8);

    Triangle t9(DownD, DownA, UpD);
    Triangle t10(UpA, DownA, UpD);
    Quad q5(t9,t10);
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
                const Vector3& leftBotomBack)
{
    Triangle triFront1(leftBotomFront,rightTopFront,leftTopFront);
    Triangle triFront2(leftBotomFront,rightBotomFront,rightTopFront);
    Triangle triRight1(rightBotomFront,rightTopBack,rightTopFront);
    Triangle triRight2(rightBotomFront,rightBotomBack,rightTopBack);
    Triangle triBack1(rightBotomBack,leftTopBack,rightTopBack);
    Triangle triBack2(rightBotomBack,leftBotomBack,leftTopBack);
    Triangle triLeft1(leftBotomBack,leftTopFront,leftTopBack);
    Triangle triLeft2(leftBotomBack,leftBotomFront,leftTopFront);
    Triangle triTop1(rightTopBack,leftTopFront,rightTopFront);
    Triangle triTop2(leftTopFront,rightTopBack,leftTopBack);
    Triangle triBotom1(rightBotomBack,leftBotomFront, leftBotomBack);
    Triangle triBotom2(rightBotomBack, rightBotomFront,leftBotomFront);

    Quad front(triFront1,triFront2);
    Quad rigth(triRight1,triRight2);
    Quad back(triBack1,triBack2);
    Quad left(triLeft1,triLeft2);
    Quad top(triTop1,triTop2);
    Quad botom(triBotom1,triBotom2);

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





