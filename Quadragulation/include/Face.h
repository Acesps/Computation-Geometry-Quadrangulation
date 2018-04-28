class HalfEdge;

#ifndef FACE_H
#define FACE_H

#include "HalfEdge.h"

using namespace std;
class Face
{
    public:

        HalfEdge *inner;
        Face();
        Face(HalfEdge *);
		int size();
        void update_inner(HalfEdge *);

        virtual ~Face();

    protected:

    private:
};

#endif // FACE_H