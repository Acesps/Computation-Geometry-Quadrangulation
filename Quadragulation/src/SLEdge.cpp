#include "SLEdge.h"
#include <limits>

SLEdge::SLEdge(double* ry)
{
	ref_y=ry;
}


bool SLEdge::operator< (const SLEdge& edge) const
{
	return  getComp(*ref_y) < edge.getComp(*ref_y) ? true : false;
}


double SLEdge::getComp(double y) const
{
	Point min = v0->point;
	if (v1->point.x < v0->point.x)
		min = v1->point;

	if (slope_inverse == numeric_limits<double>::infinity()) 
		return min.x;

	return min.x + (y - min.y) * slope_inverse;
}

bool SLEdge::atRight() const
{
	if (v0->point.y - v1->point.y == 0.0) 
	{
		if (v0->point.x < v1->point.x)
			return true;
		else 
			return false;
	}
	else if (v0->point.y - v1->point.y > 0.0) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}