#include <algorithm>
#include "Sweepline.h"
#include "RBTree.h"

#include <queue>

void SweepLine::triangulate( vector<Point>& points, vector<Triangle>& t_list, DCEL& dcel) 
{
	//DCEL dcel;
	triangulation(points, dcel);
	
	// cout<<"Done"<<endl;
	// int j=1;
	// for(auto face :dcel.f_list)
	// {
	// 	cout<<"Face:"<<j++<<endl;
	// 	cout<<face->inner->origin->p.x<<" "<<face->inner->origin->p.y<<endl;
	// 	auto i=face->inner->next;;
	// 	for( i=face->inner->next;i!=face->inner;i=i->next)
	// 		cout<<i->origin->p.x<<" "<<i->origin->p.y<<endl;
	// 	cout<<i->origin->p.x<<" "<<i->origin->p.y<<endl;

	// }

	dcel.getTriangles(t_list);	//Store DCEL triangles in t_list
}

void SweepLine::triangulation(vector<Point>& points, DCEL& dcel)
{
	if (points.size() < 3)
	{
		return;
	}
	
	if(getDirection(points)<0)
		reverse(points.begin(),points.end());

	priority_queue<SLVertexPtr> queue;		//Priority queue Q
	SLState* s = new SLState();				//Binary search tree T to control state
	s->initialize(points, dcel, queue);		// Initialize a sweepline state controller

	while (!queue.empty())
	{
		SLVertex* vertex = queue.top().ptr;
		queue.pop();

		switch (vertex->type)
		{
		case SLVertexT::START:
			// cout<<"Start"<<endl;
			start(vertex, s);
			break;
		case SLVertexT::END:
			// cout<<"End"<<endl;
			end(vertex, s);
			break;
		case SLVertexT::SPLIT:
			// cout<<"Split"<<endl;
			split(vertex, s);
			break;
		case SLVertexT::MERGE:
			// cout<<"Merge"<<endl;
			merge(vertex, s);
			break;
		case SLVertexT::REGULAR:
			// cout<<"Regular"<<endl;
			regular(vertex, s);
			break;
		}
	}
	
	dcel.triangulateYMonotone();	//Triangulate Y-Monotones created
}

//Handle Start Vertex
void SweepLine::start(SLVertex* v, SLState* s) const
{
	SLEdge* leftEdge = v->left;
	s->ref_y = v->point.y;
	s->tree.insert(leftEdge);	//Insert ei in T
	leftEdge->helper = v;		//Set helper(ei) to vi
}

//Handle End Vertex
void SweepLine::end(SLVertex* v, SLState* s) const
{
	SLEdge* r = v->right;
	if (r->helper->type == SLVertexT::MERGE) 	//If helper(ei) is a merge vertex
		s->dcel->addHalfEdges(v->index, r->helper->index);	//Insert diagonal connecting 
															//vi to helper e(i-1) in D
 	s->ref_y = v->point.y;
	s->tree.delete_value(r);	//Delete e(i-1) from T
}

//Handle Split Vertex
void SweepLine::split(SLVertex* v, SLState* s) const
{
	SLEdge* ej;
	s->tree.get_smaller(v, ej);	//Find edge ej directly left of vi in T
	s->dcel->addHalfEdges(v->index, ej->helper->index);	//Insert diagonal connecting
														//vi to helper(ej) in D
	ej->helper = v;		//Set vi as helper(ej)
	s->ref_y = v->point.y;
	s->tree.insert(v->left);	//Insert ei in T
	v->left->helper = v;		//Set helper ei to vi
}

//Handle Merge Vertex
void SweepLine::merge(SLVertex* v, SLState* s) const
{
	SLEdge* eprev = v->right;
	if (eprev->helper->type == SLVertexT::MERGE) 	//If helper(e(i-1)) is a merge vertex
		s->dcel->addHalfEdges(v->index, eprev->helper->index);	//Insert diagonal connecting
																//vi to helper(e(i-1)) in D
	s->ref_y = v->point.y;
	s->tree.delete_value(eprev);	//Delete e(i-1) from T
	SLEdge* ej;
	s->tree.get_smaller(v, ej);		//Find edge ej directly left of vi in T
	if (ej->helper->type == SLVertexT::MERGE) 	//If helper(ej) is a merge vertex
		s->dcel->addHalfEdges(v->index, ej->helper->index);		//Set vi as helper(ej)
	ej->helper = v;
}

//Handle Regular Vertex
void SweepLine::regular(SLVertex* v, SLState* s) const
{
	if (v->atRight())	//If interior of P lies to right of vi
	{
		if (v->right->helper->type == SLVertexT::MERGE) 	//If helper(e(i-1)) is a merge vertex
			s->dcel->addHalfEdges(v->index, v->right->helper->index);	//Insert diagonal connecting
																		//vi to helper(e(i-1)) in D
		s->ref_y = v->point.y;
		s->tree.delete_value(v->right);		//Delete e(i-1) from T
		s->tree.insert(v->left);			//Insert ei in T
		v->left->helper = v;			//Set helper ei to vi
	}
	else 
	{
		SLEdge* ej;
		s->tree.get_smaller(v, ej);		//Find edge ej directly left of vi in T
		if (ej->helper->type == SLVertexT::MERGE) 	//If helper(ej) is a merge vertex
			s->dcel->addHalfEdges(v->index, ej->helper->index);	//Insert diagonal connecting
																//vi to helper(ej) in D
		ej->helper = v;		//Set vi as helper(ej)
	}
}


/*
	Returns direction of polygon boundayr (clockwise/anticlockwise)
*/
double SweepLine::getDirection(const vector<Point>& points) const
{
	int n=points.size();
	auto it=min_element(points.begin(), points.end(), Point::compfunc);
	int i=distance(points.begin(), it);
	Point p1=points[i - 1 <  0 ? n-1 : i - 1];
	Point p2=points[i];
	Point p3=points[i + 1 == n ? 0 : i + 1];

	return p2.angle(p3,p1);
}