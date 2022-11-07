#ifndef POINT_H
#define POINT_H
#endif

class Point
{
    public:
    double x,y,z;

    Point();
    Point(const double,const double,const double);

    void Normalize();
};