#include "Grahams.h"

Grahams::Grahams()
{
    //ctor
}

Grahams::~Grahams()
{
    //dtor
}


using namespace std;

Point * PZero;

//comparison function for sorting
bool PCompare(Point* p1, Point* p2)
{
    int C = PZero->angle(*p1, *p2);
    if(C==0)
        return PZero->dis(*p1) <= PZero->dis(*p2) ;
    return C==1;
}

//Finding leftmost lowermost point
void Grahams::findp0()
{
    vector<Point*>::iterator p0=PList.begin();
    //taking min y point to end of array
    for(vector<Point*>::iterator it=p0+1; it!=PList.end(); ++it)
    {
        if((*it)->y < (*p0)->y || ((*it)->y == (*p0)->y && (*it)->x < (*p0)->x))
        {
            p0=it;
        }
    }
    PZero=(*p0);
    PList.erase(p0);
}



vector<Point*> Grahams::grahams(vector<Point> &vp)
{
    Hull.clear();
    PList.clear();
    for(unsigned int i=0; i<vp.size(); ++i)
            PList.push_back(&vp[i]);

    //find leftmost lowest point
    findp0();

    //sort based on angles with PZero
    sort(PList.begin(),PList.end(),PCompare);

    //remove points at same angle from PZero
    for(vector<Point*>::iterator it=PList.begin()+1; it!=PList.end(); ++it)
    {
        if(PZero->angle(**(it-1),**it)==0)
        {
            PList.erase(it-1);
            --it;
        }
    }

    //validity check
    if(PList.size()<2)
    {
        PList.clear();
        cout<<"Convex hull not possible";
        return PList;
    }

    //check for anti-clockwise turn
    Hull.push_back(PZero);
    Hull.push_back(PList[0]);
    Hull.push_back(PList[1]);
    for(vector<Point*>::iterator it=PList.begin()+1; it!=PList.end(); ++it)
    {
        while(Hull[Hull.size()-2]->angle(*Hull.back(),**it) != 1)
            Hull.pop_back();

        Hull.push_back(*it);
    }
    return Hull;

}
