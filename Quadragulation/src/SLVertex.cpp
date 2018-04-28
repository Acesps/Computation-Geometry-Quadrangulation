#include "SLVertex.h"
#include "SLEdge.h"


bool SLVertex::operator< (const SLVertex& vertex) const
{
	return point.isBelow(vertex.point);
}


bool SLVertex::atRight() const
{
	return left->atRight();
}

static double getLocation(Point p, Point lp1, Point lp2) 
{
	return (lp2.x - lp1.x) * (p.y - lp1.y) -(p.x - lp1.x) * (lp2.y - lp1.y);
}

bool SLVertex::isLeft(const SLEdge* edge) const
{
	if (getLocation(point, edge->v0->point, edge->v1->point) < 0.0)
		return true;
	else 
		return false;
}