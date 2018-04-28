#ifndef DCEL_H
#define DCEL_H

#include <vector>

#include "Vertex.h"
#include "Face.h"
#include "HalfEdge.h"
#include "Point.h"
#include "Triangle.h"


using namespace std;
class DCEL
{
    public:

        DCEL();
        virtual ~DCEL();
        void initialise(vector<Point>);
        void addHalfEdges(int i, int j);
        void addHalfEdges(Vertex* v1, Vertex* v2);
        void triangulateYMonotone();
        void getTriangles(vector<Triangle>& ) ;   

        // protected:
        Vertex* start_vertex;
        vector<Vertex*> v_list;
        vector<Face*> f_list;
        vector<HalfEdge*> e_list;

    private:
};

#endif // DCEL_H
