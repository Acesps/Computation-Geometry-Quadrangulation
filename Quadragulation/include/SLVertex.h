#ifndef SWEEPLINE_VERTEX_H
#define SWEEPLINE_VERTEX_H
#include "Point.h"
#include "SLEdge.h"

class SLEdge;

enum class SLVertexT { REGULAR, SPLIT, MERGE, START, END };

class SLVertex
{
	public:
		SLVertexT type;
		SLVertex* prev;
		SLVertex* next;

		SLEdge* left;
		SLEdge* right;

		Point point;
		int index;

		SLVertex(const Point& p, int i) : point(p), index(i) {}

		bool atRight() const;

		bool isLeft(const SLEdge* ) const;

		bool operator< (const SLVertex& ) const;
};


class SLVertexPtr
{
	public:
		SLVertex*	ptr;

		SLVertexPtr(SLVertex* ptr): ptr(ptr) {}

		bool operator< (const SLVertexPtr& v) const { return *ptr < *(v.ptr); }
};

#endif // SWEEPLINE_VERTEX_H 