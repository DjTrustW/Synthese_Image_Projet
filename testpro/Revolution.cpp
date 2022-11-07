/** Utilisation

    Revolution rbez = Revolution(dots); //dots est un std::vector<Point>
    rbez.setMeridians(12);
    rbez.setAngle(180);
    rbez.GLDraw();

**/


#include "Revolution.h"

Revolution::Revolution(const std::vector<Point> pts)
{
    (*this).pts = pts;
    (*this).NM = 24;
    (*this).color = Point(1,1,1);
    (*this).angle = 2*M_PI;
}

void Revolution::setMeridians(const unsigned n)
{
    (*this).NM = n;
}

unsigned Revolution::getMeridians()
{
    return (*this).NM;
}

void Revolution::setColor(const Point p)
{
    (*this).color = p;
}

Point Revolution::getColor()
{
    return (*this).color;
}

void Revolution::setAngle(double a)
{
    while (a > 360)
    {
        a = a - 360;
    }
    while (a < 0)
    {
        a = a + 360;
    }
    (*this).angle = 2*M_PI*a/360;
}

double Revolution::getAngle()
{   
    return (*this).angle*360/M_PI;
}

std::vector<Point> Revolution::drawPoints()
{

    std::vector<Point> pts;

    for (unsigned m = 0; m < (*this).NM; m++)
    {
        double a = m*(*this).angle/(*this).NM;

        for (Point p : (*this).pts)
        {

            double x = p.x * cos(a);
            double y = p.y;
            double z = p.x * sin(a);

            pts.push_back(Point(x,y,z));

        } 
    }

    return pts;

}

std::vector<Face4> Revolution::drawFaces()
{

    std::vector<Face4> faces;

    for (unsigned m = 0; m < (*this).NM; m++)
    {

        unsigned mn = (mn+1)%(*this).NM;

        for (unsigned i = 0; i < (*this).pts.size(); i++)
        {
            unsigned in = (i+1)% (*this).pts.size();

            unsigned a = i + m*(*this).pts.size();
            unsigned b = i + mn*(*this).pts.size();
            unsigned c = in + mn*(*this).pts.size();
            unsigned d = in + m*(*this).pts.size();

            faces.push_back(Face4(a,b,c,d));

        }
    }

    return faces;

}

void Revolution::GLDraw()
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