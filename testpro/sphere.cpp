/** Utilisation

	Sphere sun = Sphere(1);
	sun.setColor(Point(1,0.75,0));
	sun.setMeridians(60);
	sun.setParralleles(40);
	sun.GLDraw();

**/

#include "sphere.h"
#include <cmath>
#include <iostream>
#include <vector>

Sphere::Sphere()
{
    (*this).radius = 1;
    (*this).NM = 6;
    (*this).NP = 4;
    (*this).center = {0,0,0};
    (*this).color = Point(1,1,1); //this a color
}

Sphere::Sphere(const double r)
{
    (*this).radius = r;
    (*this).NM = 6;
    (*this).NP = 4;
    (*this).center = {0,0,0};
    (*this).color = Point(1,1,1);
}

Sphere::Sphere(const double r,const Point c)
{
    (*this).radius = r;
    (*this).NM = 6;
    (*this).NP = 4;
    (*this).center = c;
    (*this).color = Point(1,1,1);
}

void Sphere::setCenter(const Point c)
{
    (*this).center = c;
}

Point Sphere::getCenter()
{
    return (*this).center;
}

void Sphere::setColor(const Point c)
{
    (*this).color = c;
}

Point Sphere::getColor()
{
    return (*this).color;
}

void Sphere::setRadius(const double r)
{
    (*this).radius = r;
}

double Sphere::getRadius()
{
    return (*this).radius;
}

void Sphere::setMeridians(const unsigned n)
{
    (*this).NM = n;
}
void Sphere::setParralleles(const unsigned n)
{
    (*this).NP = n;
}

unsigned Sphere::getMeridians()
{
    return (*this).NM;
}
unsigned Sphere::getParralleles()
{
    return (*this).NP;
}

std::vector<Point> Sphere::drawPoints()
{
    //Point * pts = (Point*) malloc((*this).NM*(*this).NP);
    std::vector<Point> pts;

    for (unsigned i = 0; i < (*this).NP; i++)
    {
        for (unsigned j = 0; j < (*this).NM; j++)
        {
            double alpha = j*2*M_PI/(*this).NM;
            double teta = i*M_PI/( (*this).NP-1) - M_PI/2;
            double x = (*this).center.x + (*this).radius*cos(alpha)*cos(teta);
            double y = (*this).center.y + (*this).radius*sin(alpha)*cos(teta);
            double z = (*this).center.z + (*this).radius*sin(teta);
            pts.push_back(Point(x,y,z));
        }
    }

    return pts;

}

std::vector<Face4> Sphere::drawFaces()
{
    //Face4 * faces = (Face4*) malloc((*this).NM*(*this).NP - (*this).NM);
    std::vector<Face4> faces;

    for (unsigned i = 0; i < (*this).NP-1; i++)
    {
        for (unsigned j = 0; j < (*this).NM; j++)
        {

            unsigned in = (i+1)%(*this).NP;
            unsigned jn = (j+1)%(*this).NM;

            unsigned p0 = i*(*this).NM + j;
            unsigned p1 = i*(*this).NM + jn;
            unsigned p2 = in*(*this).NM + jn;
            unsigned p3 = in*(*this).NM + j;
            faces.push_back(Face4(p0, p1, p2, p3));
        }
    }

    return faces;
}

void Sphere::GLDraw()
{

    std::vector<Point> pts = (*this).drawPoints();
    std::vector<Face4> faces = (*this).drawFaces();

    for (Face4 f : faces)
    {
        glBegin(GL_POLYGON);
        for (short i=0;i<4;i++){
            Point p = pts[f.getPoint(i)];
            glColor3f((*this).color.x, (*this).color.y, (*this).color.z);
            glVertex3f(p.x,p.y,p.z);
        }
        glEnd();
    }
}
