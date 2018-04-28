#include "HalfEdge.h"

HalfEdge::HalfEdge()
{
    //ctor
}

HalfEdge::~HalfEdge()
{
    //dtor
}

HalfEdge::HalfEdge(Vertex* a)
{
    origin=a;
    a->update_origin(this);
}

void  HalfEdge::make_twin(HalfEdge* he)
{
    twin=he;
    he->twin=this;
}

void HalfEdge::set_next(HalfEdge* he)
{
    next=he;
    he->prev=this;
}

void HalfEdge::set_prev(HalfEdge* he)
{
    prev=he;
    he->next=this;
}

void HalfEdge::set_face(Face* face)
{
    ref_face=face;
}