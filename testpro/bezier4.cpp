#include "bezier4.h"
#include <cmath>
#include <vector>
#include <cstdio>

Bezier4::Bezier4(const Point a, const Point b, const Point c, const Point d)
{

    (*this).a = a;
    (*this).b = b;
    (*this).c = c;
    (*this).d = d;
    (*this).DEF = 12;

}

void Bezier4::setDefinition(const unsigned n)
{
    (*this).DEF = n;
}
/** Utilisation

//On s'en branle du Z 
Point a = Point(0,0,0);
Point b = Point(6,6,0);
Point c = Point(0,6,0);
Point d = Point(0,1,0);

Bezier4 bez = Bezier4(a,b,c,d);
bez.setDefinition(12);
std::vector<Point> dots = bez.Spline(); //-> voir avec Revolution

**/

unsigned Bezier4::getDefinition()
{
    return (*this).DEF;
}

std::vector<Point> Bezier4::Spline()
{
    //lets do the maths
    std::vector<Point> pts;

    Point a = (*this).a;
    Point b = (*this).b;
    Point c = (*this).c;
    Point d = (*this).d;
    double p = (*this).DEF;

    for (double t = 0; t < p; t++)
    {
        double x = a.x*pow((1-(t/p)),3) + b.x*3*(t/p)*pow((1-(t/p)),2) + c.x*3*((t/p)*(t/p))*(1-(t/p)) + d.x*pow((t/p),3);
        double y = a.y*pow((1-(t/p)),3) + b.y*3*(t/p)*pow((1-(t/p)),2) + c.y*3*((t/p)*(t/p))*(1-(t/p)) + d.y*pow((t/p),3);
        pts.push_back(Point(x,y,0));
    }

    return pts;
}