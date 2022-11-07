#ifndef SPHERE_H
#define SPHERE_H
#endif

#ifndef POINT_H
#include "point.h"
#endif
#ifndef FACE4_H
#include "face4.h"
#endif
#include <vector>
#include <GL/glut.h>

class Sphere 
{
    private:
    
    double radius;
    Point center;
    unsigned NM;
    unsigned NP;
    Point color;

    public:

    Sphere();
    Sphere(const double);
    Sphere(const double, const Point);

    void setCenter(const Point);
    Point getCenter();

    void setColor(const Point);
    Point getColor();

    void setRadius(const double);
    double getRadius();

    void setMeridians(const unsigned);
    void setParralleles(const unsigned);

    unsigned getMeridians();
    unsigned getParralleles();

    std::vector<Point> drawPoints();
    std::vector<Face4> drawFaces();

    void GLDraw();

};