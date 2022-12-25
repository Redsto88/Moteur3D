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
    /*Les qautres points de la base du quadrilatère*/
    Vector3 DownA = _quad.getT1().getA();
    Vector3 DownB = _quad.getT1().getB();
    Vector3 DownC = _quad.getT1().getC();
    Vector3 DownD = _quad.getT2().getA();

    Vector3 g = a + Vector3(0,0,height);
    Vector3 h = b + Vector3(0,0,height);
    Vector3 i = c + Vector3(0,0,height);
    Vector3 j = d + Vector3(0,0,height);
    Vector3 k = e + Vector3(0,0,height);
    Vector3 l = f + Vector3(0,0,height);

    Triangle3D t1(a,b,c);
    Triangle3D t2(d,e,f);
    Triangle3D t3(a,d,g);
    Triangle3D t4(d,g,j);
    Triangle3D t5(b,e,h);
    Triangle3D t6(e,h,k);
    Triangle3D t7(c,f,i);
    Triangle3D t8(f,i,l);
    Triangle3D t9(a,b,h);
    Triangle3D t10(a,h,g);
    Triangle3D t11(d,e,k);
    Triangle3D t12(d,k,j);
    Triangle3D t13(g,h,k);
    Triangle3D t14(g,k,j);
    Triangle3D t15(c,b,h);
    Triangle3D t16(c,h,i);
    Triangle3D t17(f,e,k);
    Triangle3D t18(f,k,l);
    Triangle3D t19(i,j,k);
    Triangle3D t20(i,k,l);

    Quad3D q1(t1,t2);
    Quad3D q2(t3,t4);
    Quad3D q3(t5,t6);
    Quad3D q4(t7,t8);
    Quad3D q5(t9,t10);
    Quad3D q6(t11,t12);
    Quad3D q7(t13,t14);
    Quad3D q8(t15,t16);
    Quad3D q9(t17,t18);
}

