#include "Vertex.h"

Vertex::Vertex()
{
    p=Point(0,0);
}

Vertex::Vertex(Point x)
{
    p=x;
}

Vertex::~Vertex()
{
    //dtor
}

//Update incident edge
void Vertex::update_origin(HalfEdge* he)
{
	incident=he;
}
