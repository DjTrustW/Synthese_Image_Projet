#include "point.h"
#include <cmath>

Point::Point()
{
    (*this).x = 0;
    (*this).y = 0;
    (*this).z = 0;
}

Point::Point(const double x, const double y, const double z)
{
    (*this).x = x;
    (*this).y = y;
    (*this).z = z;
}

void Point::Normalize()
{

    double r = sqrt((*this).x*(*this).x + (*this).y*(*this).y + (*this).z*(*this).z);

    (*this).x = (*this).x * r;
    (*this).y = (*this).y * r;
    (*this).z = (*this).z * r;
}
