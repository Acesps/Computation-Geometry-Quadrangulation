#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point.h"

class Triangle
{
public:
	Point point1;
	Point point2;
	Point point3;

	Triangle(){};

	Triangle(const Point& point1, const Point& point2, const Point& point3)
		: point1(point1)
		, point2(point2)
		, point3(point3)
	{}
};

#endif // TRIANGLE_H 
