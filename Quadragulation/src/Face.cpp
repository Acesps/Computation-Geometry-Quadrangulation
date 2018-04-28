#include "Face.h"

Face::Face()
{
    //ctor
}

Face::Face(HalfEdge * he)
{
    update_inner(he);
}

Face::~Face()
{
    //dtor
}

/*
	Updates containing edge of face
*/
void Face::update_inner(HalfEdge * he)
{
	inner=he;
	he->set_face(this);

	for(HalfEdge *te = he->next; te->ref_face != this; te=te->next)
		te->set_face(this);
}

/*
	Returns number of edges in face
*/
int Face::size()
{
	int i=1;
	for(HalfEdge *te = inner->next; te!=inner; te=te->next)
		++i;
	return i;
}