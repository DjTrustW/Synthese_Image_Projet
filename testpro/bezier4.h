#ifndef BEZIER4_H
#define BEZIER4_H
#endif

#include <cmath>
#include <vector>

#ifndef POINT_H
#include "point.h"
#endif

class Bezier4
{

    private:

    Point a,b,c,d;
    unsigned DEF;

    public:

    Bezier4(const Point, const Point, const Point, const Point);

    void setDefinition(const unsigned);
    unsigned getDefinition();

    std::vector<Point> Spline();

};