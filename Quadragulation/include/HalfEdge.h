class Vertex;
class Face;

#ifndef HALFEDGE_H
#define HALFEDGE_H

#include "Vertex.h"
#include "Face.h"

using namespace std;
class HalfEdge
{
    public:
        Vertex* origin;
        Face* ref_face;
        HalfEdge *twin, *next, *prev;

        HalfEdge();
        HalfEdge(Vertex *);

        void make_twin(HalfEdge *);
        void set_prev(HalfEdge *);
        void set_next(HalfEdge *);
        void set_face(Face *);

        virtual ~HalfEdge();

    protected:

    private:
};

#endif // HALFEDGE_H
