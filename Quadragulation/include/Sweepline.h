#ifndef SWEEPLINE_H
#define SWEEPLINE_H

#include <vector>
#include <list>

#include "Point.h"
#include "SLVertex.h"
#include "SLState.h"
#include "SLEdge.h"
#include "DCEL.h"
#include "Triangle.h"

class SLVertex;
class SLState;
class SLEdge;

using namespace std;

class SweepLine
{

public:
	void triangulate(  vector<Point>& , vector<Triangle>& , DCEL& ) ;
	
	void triangulation( vector<Point>& , DCEL& ) ;

private:
	void start		(SLVertex* , SLState* ) const;
	void end		(SLVertex* , SLState* ) const;
	void split		(SLVertex* , SLState* ) const;
	void merge		(SLVertex* , SLState* ) const;
	void regular	(SLVertex* , SLState* ) const;
	double getDirection(const vector<Point>& ) const;
};


#endif // SWEEPLINE_H 