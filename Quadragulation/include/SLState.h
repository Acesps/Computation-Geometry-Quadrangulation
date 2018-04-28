#ifndef SWEEPLINE_STATE_H
#define SWEEPLINE_STATE_H

#include <queue>
#include <vector>
#include "DCEL.h"
#include "SLVertex.h"
#include "SLEdge.h"
#include "RBTree.h"

class SLVertex;
class SLEdge;


class Compare
{
public:
	bool less(SLVertex* vertex, SLEdge * edge) const;
	bool less(SLEdge* edge, SLVertex* vertex) const;
	bool less(SLEdge* e1, SLEdge* e2) const;
};


class SLState
{
public:
	
	DCEL* dcel;
	double ref_y;
	RBTree<SLEdge *, SLVertex *, Compare> tree;

	SLState()=default;
	
	void initialize(const vector<Point>& points, DCEL& dcel, priority_queue<SLVertexPtr>& queue);

private:
	
	SLVertexT getType( const Point& point_left, const Point& point, const Point& point_right) const;
};


#endif // SWEEPLINE_STATE_H 