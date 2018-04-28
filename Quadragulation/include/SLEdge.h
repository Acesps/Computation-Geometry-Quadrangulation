#ifndef SWEEPLINE_EDGE_H
#define SWEEPLINE_EDGE_H
#include "SLVertex.h"

class SLVertex;

class SLEdge
{
	public:

		SLVertex* v0;
		SLVertex* v1;

		SLVertex* helper;

		double slope_inverse;
		double* ref_y;

		double getComp(double) const;

		bool atRight() const;

		bool operator< (const SLEdge& ) const;

		SLEdge(double* );

};

#endif // SWEEPLINE_EDGE_H 