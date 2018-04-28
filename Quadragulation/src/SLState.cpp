#include "SLState.h"
#include "SLVertex.h"
#include "SLEdge.h"

#include <limits>

using namespace std;


bool Compare::less(SLVertex* vertex, SLEdge * edge) const
{
	if (vertex->isLeft(edge))
		return true;
	else 
		return false;
}
bool Compare::less(SLEdge* edge, SLVertex* vertex) const
{
	if (vertex->isLeft(edge)) 
		return false;
	else 
		return true;
}
bool Compare::less(SLEdge* e1, SLEdge* e2) const
{
	if (e1 == e2)
		return false;
	
	double y = *(e1->ref_y);

	if (e1->getComp(y) < e2->getComp(y))
		return false;
	else 
		return true;
}

void SLState::initialize( const vector<Point>& points, DCEL& dcel, priority_queue<SLVertexPtr>& queue)
{
	dcel.initialise(points);
	this->dcel = &dcel;

	int n = points.size();

	SLVertex*  vroot = nullptr;
	SLVertex*  vprev = nullptr;

	SLEdge*	  eroot   = nullptr;
	SLEdge*	  eprev   = nullptr;

	for (int i = 0; i < n; i++)
	{
		Point p = points[i];

		SLVertex* v = new SLVertex(p, i);
		v->type = SLVertexT::REGULAR;
		v->prev = vprev;

		if (vprev != nullptr)
			vprev->next = v;

		if (vroot == nullptr)
			vroot = v;

		Point p1 = points[i + 1 == n ? 0 : i + 1];
		Point p0 = points[i == 0 ? n - 1 : i - 1];
		
		v->type = getType(p0, p, p1);
		vprev = v;
		queue.push(SLVertexPtr(v));

		SLEdge* e = new SLEdge(&ref_y);
		e->v0 = v;

		if (p.y - p1.y == 0.0)
			e->slope_inverse = numeric_limits<double>::infinity();
		else
			e->slope_inverse = (p.x - p1.x / p.y - p1.y);

		if (eprev != nullptr)
			eprev->v1 = v;

		if (eroot == nullptr)
			eroot = e;

		v->left = e;
		v->right = eprev;

		eprev = e;
	}

	eprev->v1 = eroot->v0;

	vroot->right = eprev;
	vroot->prev  = vprev;
	vprev->next  = vroot;
}

SLVertexT SLState::getType( const Point& pl, const Point& p, const Point& pr) const
{
	Point v1 = pl.to(p);
	Point v2 = p.to(pr);
	double cross = v1.cross(v2);

	bool ltP0 = p.isBelow(pl);
	bool ltP1 = p.isBelow(pr);

	if (ltP0 && ltP1) 
	{
		if (cross > 0.0)
			return SLVertexT::END;
		else
			return SLVertexT::MERGE;
	} 
	else if (!ltP0 && !ltP1) 
	{
		if (cross > 0.0)
			return SLVertexT::START;
		else
			return SLVertexT::SPLIT;
	}

	return SLVertexT::REGULAR;
}


