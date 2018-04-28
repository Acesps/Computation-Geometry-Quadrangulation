#include <algorithm>
#include <stack>
#include <iostream>
#include "DCEL.h"

DCEL::DCEL()
{
    //ctor
}


DCEL::~DCEL()
{
	for (auto edge : e_list)			delete edge;
	for (auto vertex : v_list)	delete vertex;
	for (auto face : f_list)			delete face;
}

/* 
	Function initialises a DCEL given polygon boundary
*/
void DCEL::initialise(vector<Point> p_list)
{
	Vertex* v0= new Vertex(p_list.front());
	v_list.push_back(v0);
	Vertex* v1;

	HalfEdge* e0= new HalfEdge(v0);
	HalfEdge* t0= new HalfEdge(v0);
	HalfEdge* e1;
	HalfEdge* t1;
	e_list.push_back(e0);
	e_list.push_back(t0);

	HalfEdge* se1=e0, *st1=t0;

	for(vector<Point>::iterator i = p_list.begin()+1; i!=p_list.end(); ++i)
	{
		v1=new Vertex(*i);
		e1=new HalfEdge(v1);
		t1=new HalfEdge(v1);
		e0->set_next(e1);
		t0->set_prev(t1);
		e0->make_twin(t1);
		v_list.push_back(v1);
		e_list.push_back(e1);
		e_list.push_back(t1);

		e0=e1;
		v0=v1;
		t0=t1;
	}
	e0->set_next(se1);
	t0->set_prev(st1);
	e0->make_twin(st1);

	
	Vertex* o=*min_element(v_list.begin(),v_list.end(),Vertex::compfunc);
	HalfEdge* te1 =o->incident->twin;
	HalfEdge* te2= o->incident->twin->next->twin;

	if( (o->p).angle(te1->origin->p,te2->origin->p)==1 )
		f_list.push_back(new Face(te2));
	else
		f_list.push_back(new Face(te1));

}


/*
	Add a half edge given indices of vertices
*/
void DCEL::addHalfEdges(int i, int j)
{
	auto iter_i = next(v_list.begin(), i);
	auto vertex1 = *iter_i;
	auto iter_j = next(v_list.begin(), j);
	auto vertex2 = *iter_j;
	
	addHalfEdges(vertex1, vertex2);
}


/*
	Add a half edge given pointer to vertices
*/
void DCEL::addHalfEdges(Vertex* v1, Vertex* v2)
{
	
	cout<<"Adding edge:\t("<<v1->p.x<<" , "<<v1->p.y<<") to ("<<v2->p.x<<" , "<<v2->p.y<<")"<<endl;
	HalfEdge *s1=v1->incident;
	HalfEdge *s2=v2->incident;
	HalfEdge *e1, *e2;
	e2=s2->twin;
	while(s1->ref_face != s2->ref_face || s1->ref_face==nullptr)
	{
		e1=s1;
		do
		{
			e2=s2;		
			do
			{
				if(e1->ref_face == e2->ref_face)
					break;
				e2=e2->twin->next;
			}	while(e2!=s2);
			
			if(e1->ref_face == e2->ref_face && e1->ref_face!=nullptr)
			{	
				s1=e1;
				s2=e2;
				break;
			}
			e1=e1->twin->next;
		
		} while(e1!=s1);
	}

	HalfEdge* edge1 = new HalfEdge(v1);
	HalfEdge* edge2 = new HalfEdge(v2);

	edge1->make_twin(edge2);
	edge1->set_prev(s1->prev);
	edge2->set_prev(s2->prev);
	edge1->set_next(s2);
	edge2->set_next(s1);

	s1->ref_face->update_inner(edge2);

	Face* face= new Face(edge1);

	e_list.push_back(edge1);
	e_list.push_back(edge2);

	f_list.push_back(face);
	int j=1;
	// for(auto face :f_list)
	// {
	// 	cout<<"Face:"<<j++<<endl;
	// 	cout<<face->inner->origin->p.x<<" "<<face->inner->origin->p.y<<endl;
	// 	auto i=face->inner->next;;
	// 	for( i=face->inner->next;i!=face->inner;i=i->next)
	// 		cout<<i->origin->p.x<<" "<<i->origin->p.y<<endl;
	// 	cout<<i->origin->p.x<<" "<<i->origin->p.y<<endl;

	// }
}


/*
	Function to triangulate Y-Monotones
	***Must be called only after splitting polygon into Y-Monotones***
*/
void DCEL::triangulateYMonotone()
{
	int i=1;
	auto tf_list=f_list;
	for(auto face : tf_list)
	{

		if(face->size()<=3)
			continue;
		HalfEdge* bottome=face->inner;


		for(bottome=face->inner; Vertex::compfunc(bottome->origin, bottome->next->origin); bottome=bottome->next);
		for(; Vertex::compfunc(bottome->origin, bottome->prev->origin); bottome=bottome->prev);

		Vertex* bottomv= bottome->origin;
		vector<Vertex*> lchain;		//left chain
		vector<Vertex*> rchain;		//right chain
		vector<Vertex*> vstack;		//Initialise empty stack

		for(HalfEdge* he =bottome->next; Vertex::compfunc(he->origin, he->prev->origin); he=he->next)
			lchain.push_back(he->origin);
		for(HalfEdge* he =bottome->prev; Vertex::compfunc(he->origin, he->next->origin); he=he->prev)
			rchain.push_back(he->origin);


		Vertex* topv= rchain.back();
			lchain.pop_back();
			rchain.pop_back();
			int control=-1;
			while(lchain.size()!=0 || rchain.size()!=0)
			{
				vstack.push_back(topv);		//Push u1

				//Iterate only fo
				if(rchain.size()==0 || Vertex::compfunc(lchain.back(),rchain.back()))
				{	
					lchain.swap(rchain);
					control*=-1;
				}	
				while(rchain.size()>0 && (lchain.size()==0 || Vertex::compfunc(rchain.back(),lchain.back()) ) )
				{
					//Pop till diagonals from uj are inside P
					while(vstack.size()>1 && rchain.back()->p.angle(vstack.back()->p,vstack.rbegin()[1]->p)==control)
					{
						vstack.pop_back();
						addHalfEdges(rchain.back(),vstack.back());	//Insert these diagonals into D
					}
					vstack.push_back(rchain.back());	//Push last vertex back on to S
					rchain.pop_back();	
				}


				topv=vstack.back();
				if(lchain.size()==0)
					vstack.pop_back();
				while(vstack.size()>1)		//For all stack vertices except the last one
				{
					addHalfEdges(lchain.back(),vstack.back());	//Insert diagonal from un
					vstack.pop_back();		//Pop vertices
				}	
				vstack.pop_back();	//** Diagonal not inserted for last vertex

			}

	}
}


/*
	Returns a list of triangles in the DCEL
	***Must be called only after complete triangulation***
*/
void DCEL::getTriangles(vector<Triangle>& t_list)
{
	for(auto face :f_list)
		t_list.push_back(Triangle(face->inner->origin->p, face->inner->next->origin->p, face->inner->next->next->origin->p));
}

