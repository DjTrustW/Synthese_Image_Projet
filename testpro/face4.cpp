#include "face4.h"

Face4::Face4(const unsigned p0, const unsigned p1, const unsigned p2, const unsigned p3)
{
    (*this).p0 = p0;
    (*this).p1 = p1;
    (*this).p2 = p2;
    (*this).p3 = p3;
}

unsigned* Face4::getPoints()
{
    unsigned * pts = new unsigned[4];
    pts[0] = (*this).p0;
    pts[1] = (*this).p1;
    pts[2] = (*this).p2;
    pts[3] = (*this).p3;

    return pts;
}

unsigned Face4::getPoint(unsigned short n)
{
    if (n == 0) {return (*this).p0;}
    if (n == 1) {return (*this).p1;}
    if (n == 2) {return (*this).p2;}
    if (n == 3) {return (*this).p3;}
    else {return 0;}
}
