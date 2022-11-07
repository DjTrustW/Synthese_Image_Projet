#ifndef FACE4_H
#define FACE4_H
#endif

class Face4
{
    public:
    unsigned p0,p1,p2,p3;
    Face4(const unsigned, const unsigned, const unsigned, const unsigned);

    unsigned* getPoints();
    unsigned getPoint(unsigned short);
};