#ifndef CYLINDER_H
#define CYLINDER_H
#endif

#ifndef POINT_H
#include "point.h"
#endif
#ifndef FACE4_H
#include "face4.h"
#endif
#include <vector>
#include <GL/glut.h>

class Cylinder 
{
    private:
    
    double radius;
    Point start;
    Point end;
    unsigned DEF;
    Point color;

    public:

    Cylinder();
    Cylinder(const double);
    Cylinder(const double, const Point, const Point);

    void setStart(const Point);
    Point getStart();

    void setEnd(const Point);
    Point getEnd();

    void setColor(const Point);
    Point getColor();

    void setRadius(const double);
    double getRadius();

    void setDefinition(const unsigned);
    unsigned getDefinition();

    std::vector<Point> drawPoints();
    std::vector<Face4> drawFaces();

    void GLDraw();

};