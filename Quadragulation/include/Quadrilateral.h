#ifndef Quadrilateral_H
#define Quadrilateral_H

#include "Point.h"

class Quadrilateral
{
public:
	Point point1;
	Point point2;
	Point point3;
	Point point4;

	Quadrilateral(){};

	Quadrilateral(const Point& point1, const Point& point2, const Point& point3, const Point& point4)
		: point1(point1)
		, point2(point2)
		, point3(point3)
		, point4(point4)
	{}
};

#endif // Quadrilateral_H 
