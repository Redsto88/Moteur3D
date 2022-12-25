#include "Pave3D.hpp"
#include "vector3.hpp"

Pave3D::Pave3D(std::vector<Quad3D> _quads)
{
    quads = _quads;
}

Pave3D::Pave3D(const Pave3D& _pave)
{
    quads = _pave.getQuads();
}

Pave3D::Pave3D(const Quad3D& _quad, float height)
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
    Triangle3D t1(UpA, UpB, UpC);
    Triangle3D t2(UpD, UpB, UpC);
    Quad3D q1(t1,t2);

    /*Les triangles des côtés*/
    Triangle3D t3(DownA, DownB, UpA);
    Triangle3D t4(UpB, DownB, UpA);
    Quad3D q2(t3,t4);

    Triangle3D t5(DownB, DownC, UpB);
    Triangle3D t6(UpC, DownC, UpB);
    Quad3D q3(t5,t6);

    Triangle3D t7(DownC, DownD, UpC);
    Triangle3D t8(UpD, DownD, UpC);
    Quad3D q4(t7,t8);

    Triangle3D t9(DownD, DownA, UpD);
    Triangle3D t10(UpA, DownA, UpD);
    Quad3D q5(t9,t10);

    quads = std::vector<Quad3D>();
    quads.push_back(_quad);
    quads.push_back(q1);
    quads.push_back(q2);
    quads.push_back(q3);
    quads.push_back(q4);
    quads.push_back(q5);
}

