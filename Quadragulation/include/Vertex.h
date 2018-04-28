class HalfEdge;

#ifndef VERTEX_H
#define VERTEX_H

#include "Point.h"
#include "HalfEdge.h"

using namespace std;
class Vertex
{
    public:
        Point p;
        HalfEdge* incident;
        Vertex();
        Vertex(Point);
        
        void update_origin(HalfEdge*);
        static bool compfunc(Vertex *i, Vertex *j)
        {
        	return ((i->p).y>(j->p).y || ((i->p).y == (j->p).y && (i->p).x < (j->p).x));
        }
        
        virtual ~Vertex();

    protected:

    private:

};

#endif // VERTEX_H
