#include "Jarvis.h"

Jarvis::Jarvis()
{
    //ctor
}

Jarvis::~Jarvis()
{
    //dtor
}

using namespace std;

vector<Point*> Jarvis::jarvis(vector<Point> &PList)
{
    Hull.clear();

    //find leftmost lowest point
    vector<Point>::iterator p0=PList.begin();
    for(vector<Point>::iterator it=p0+1; it!=PList.end(); ++it)
    {
        if(it->y < p0->y || (it->y == p0->y && it->x < p0->x))
        {
            p0=it;
        }
    }

    vector<Point>::iterator temp=p0;

    //get hull
	do{
        Hull.push_back(&(*temp));
 		temp = PList.begin();
        for(vector<Point>::iterator it=PList.begin()+1; it!=PList.end(); ++it)
		{
		    //find furthest point with least angle
		    if(Hull.back()->angle(*it,*temp) == 1 || (Hull.back()->angle(*it,*temp) == 0 && Hull.back()->dis(*it) > Hull.back()->dis(*temp)))
				temp=it;
		}
	}while(Hull.front() != &(*temp));

	//validity check
    if(Hull.size()<=2)
    {
        cout<<"Convex hull not possible";
        Hull.clear();
    }
    return Hull;

}
