#include "Point.h"

const double Epsilon = 4.94065645841247E-324;

Point::Point()
{
    x=0;
    y=0;
}

Point::Point(double a, double b)
{
    x=a;
    y=b;
}

Point::~Point()
{
    //dtor
}


bool Point::isBelow(const Point& p) const
{
    return (y<p.y || (y == p.y && x > p.x));
}

//Returns orientation of b-c wrt current point
int Point::angle(Point b, Point c)
{
    int val = to(b).cross(b.to(c));

    if (val < 0.005 && val > -0.005) return 0;  // colinear
    return (val > 0)? 1: -1; //  counterclock or clock wise
}

double  Point::cross(const Point& p) const
{
    return x * p.y - y * p.x;
}

//Returns distance of t from current point
double Point::dis(Point t)
{
    return (x-t.x)*(x-t.x) + (y-t.y)*(y-t.y);
}

//Returns slope of t wrt current point
double Point::slope(Point t)
{
    return (y-t.y)/(x-t.x);
}

//Returns the intercept of line with slope K passing through current point
double Point::intersect(double K)
{
    return y - K * x;
}

Point Point::to(const Point &p) const
{
    return Point(p.x-x, p.y-y);
}

