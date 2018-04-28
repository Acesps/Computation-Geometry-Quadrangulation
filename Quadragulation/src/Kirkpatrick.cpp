#include "Kirkpatrick.h"

Kirkpatrick::Kirkpatrick()
{
    //ctor
}

Kirkpatrick::~Kirkpatrick()
{
    //dtor
}

using namespace std;

bool Compare (Point* i, Point* j) { return (i->x < j->x)||((i->x == j->x)&&(i->y < j->y)); }


//function to get boundary points
void findpmin(vector<Point> &PList, Point **Pumin, Point **Pumax,  Point **Plmin,  Point **Plmax)
{

	*Pumin = &(*PList.begin());
	*Pumax = &(*PList.begin());
	*Plmin = &(*PList.begin());
	*Plmax = &(*PList.begin());

    for(vector<Point>::iterator it=PList.begin()+1; it!=PList.end(); ++it)
    {
        if(it->x > (*Pumax)->x)
        {
			*Pumax = &(*it);
            *Plmax = &(*it);
		}
        else if(it->x == (*Pumax)->x)
        {
            if (it->y > (*Pumax)->y)
                *Pumax = &(*it);

            if (it->y < (*Plmax)->y)
                *Plmax = &(*it);
        }

        if(it->x < (*Pumin)->x)
        {
			*Pumin = &(*it);
            *Plmin = &(*it);
		}
        else if(it->x == (*Pumin)->x)
        {
            if (it->y > (*Pumin)->y)
                *Pumin = &(*it);

            if (it->y < (*Plmin)->y)
                *Plmin = &(*it);
        }
	}
}

//function returns vector of all points with anti-clockwise rotation wrt p1, p2
vector<Point*> divide(Point* p1, Point* p2, vector<Point*> &PList)
{
	vector<Point*> T;
	if(p1->x == p2->x && p1->y == p2->y){
    	T.push_back(p1);
		return T;
	}

    for(vector<Point*>::iterator it=PList.begin(); it!=PList.end(); ++it)
		if(p1->angle(*p2,**it) ==1)
			T.push_back(*it);

	T.push_back(p1);
	T.push_back(p2);
	return T;
}

//function to find upper bridge
void upperBridge(vector<Point*> PList, Point **pl, Point **pr, int a){

	vector<Point*> candidates;

	if(PList.size() == 2){
		if(PList[0]->x > PList[1]->x){
			swap(PList[0], PList[1]);
		}
		*pl = PList[0];
		*pr = PList[1];
		return;
	}

	if(PList.size() % 2){
		candidates.push_back(PList.back());
		PList.pop_back();
	}
	vector<double> slopes;
    for(vector<Point*>::iterator it=PList.begin(); it!=PList.end(); it+=2)
    {
        vector<Point*>::iterator jt=it+1;
		if((*it)->x == (*jt)->x){
			if((*it)->y > (*jt)->y)
				candidates.push_back(*it);
			else
				candidates.push_back(*jt);
            PList.erase(it);
            PList.erase(it);
            it-=2;
		}
		else
        {
            if((*it)->x > (*jt)->x)
                swap(*it, *jt);
            slopes.push_back((*it)->slope(**jt));
        }
	}

	//5.median of slopes
	if(slopes.size())
    {
        nth_element(slopes.begin(), slopes.begin() + slopes.size()/2, slopes.end());
        double K = slopes[slopes.size()/2];
        slopes.clear();
        //6.
        vector<Point*> SMALL, EQUAL, LARGE;
        for(vector<Point*>::iterator it=PList.begin(); it!=PList.end(); it+=2)
        {
            vector<Point*>::iterator jt=it+1;
            double k = (*it)->slope(**jt);
            if(K > k){
                SMALL.push_back(*it);
                SMALL.push_back(*jt);
            }
            else if(K == k){
                EQUAL.push_back(*it);
                EQUAL.push_back(*jt);
            }
            else{
                LARGE.push_back(*it);
                LARGE.push_back(*jt);
            }
        }
        //7.
        PList.insert(PList.end(),candidates.begin(),candidates.end());

        Point *pk=*PList.begin();
        Point *pm=pk;
        double maxint = (*PList.begin())->intersect(K);
        for(vector<Point*>::iterator it=PList.begin(); it!=PList.end(); ++it)
        {
            double tempint = (*it)->intersect(K);
            if(maxint == tempint){
                if((*it)->x < pk->x)
                    pk=*it;
                else if((*it)->x > pm->x)
                    pm=*it;
            }
            else if(maxint < tempint){
                maxint = tempint;
                    pk=*it;
                    pm=*it;
            }
        }

        //8.
        if(pk->x <= a && pm->x > a){
            *pl = pk;
            *pr = pm;
            return;
        }
        //9.
        if(pm->x <= a){
            for(vector<Point*>::iterator it=LARGE.begin(); it!=LARGE.end(); it+=2)
                candidates.push_back(*(it+1));
            for(vector<Point*>::iterator it=EQUAL.begin(); it!=EQUAL.end(); it+=2)
                candidates.push_back(*(it+1));
            for(vector<Point*>::iterator it=SMALL.begin(); it!=SMALL.end(); it+=2)
            {
                candidates.push_back(*it);
                candidates.push_back(*(it+1));
            }
        }
        //10.
        else if(pk->x > a){
            for(vector<Point*>::iterator it=SMALL.begin(); it!=SMALL.end(); it+=2)
                candidates.push_back(*it);
            for(vector<Point*>::iterator it=EQUAL.begin(); it!=EQUAL.end(); it+=2)
                candidates.push_back(*it);
            for(vector<Point*>::iterator it=LARGE.begin(); it!=LARGE.end(); it+=2)
            {
                candidates.push_back(*it);
                candidates.push_back(*(it+1));
            }
        }
    }

	return upperBridge(candidates, pl, pr, a);
}


//function to find lower bridge
void lowerBridge(vector<Point*> PList, Point **pl, Point **pr, int a){
	vector<Point*> candidates;

    if(PList.size() == 2){
		if(PList[0]->x > PList[1]->x){
			swap(PList[0], PList[1]);
		}
		*pl = PList[0];
		*pr = PList[1];
		return;
	}

    if(PList.size() % 2){
		candidates.push_back(PList.back());
		PList.pop_back();
	}
	vector<double> slopes;
    for(vector<Point*>::iterator it=PList.begin(); it!=PList.end(); it+=2)
    {
        vector<Point*>::iterator jt=it+1;
		if((*it)->x == (*jt)->x){
			if((*it)->y < (*jt)->y)
				candidates.push_back(*it);
			else
				candidates.push_back(*jt);
            PList.erase(it);
            PList.erase(it);
            it-=2;
		}
		else
        {
            if((*it)->x > (*jt)->x)
                swap(*it, *jt);
            slopes.push_back((*it)->slope(**jt));
        }
	}

	//5.median of slopes
	if(slopes.size())
    {
        nth_element(slopes.begin(), slopes.begin() + slopes.size()/2, slopes.end());
        double K = slopes[slopes.size()/2];
        slopes.clear();
        //6.
        vector<Point*> SMALL, EQUAL, LARGE;
        for(vector<Point*>::iterator it=PList.begin(); it!=PList.end(); it+=2)
        {
            vector<Point*>::iterator jt=it+1;
            double k = (*it)->slope(**jt);
            if(K < k){
                SMALL.push_back(*it);
                SMALL.push_back(*jt);
            }
            else if(K == k){
                EQUAL.push_back(*it);
                EQUAL.push_back(*jt);
            }
            else{
                LARGE.push_back(*it);
                LARGE.push_back(*jt);
            }
        }
        //7.
        PList.insert(PList.end(),candidates.begin(),candidates.end());

        Point *pk=*PList.begin();
        Point *pm=pk;
        double maxint = (*PList.begin())->intersect(K);
        for(vector<Point*>::iterator it=PList.begin(); it!=PList.end(); ++it)
        {
            double tempint = (*it)->intersect(K);
            if(maxint == tempint){
                if((*it)->x < pk->x)
                    pk=*it;
                else if((*it)->x > pm->x)
                    pm=*it;
            }
            else if(maxint > tempint){
                maxint = tempint;
                    pk=*it;
                    pm=*it;
            }
        }

        //8.
        if(pk->x <= a && pm->x > a){
            *pl = pk;
            *pr = pm;
            return;
        }

        //9.
        if(pm->x <= a){
            for(vector<Point*>::iterator it=LARGE.begin(); it!=LARGE.end(); it+=2)
                candidates.push_back(*(it+1));
            for(vector<Point*>::iterator it=EQUAL.begin(); it!=EQUAL.end(); it+=2)
                candidates.push_back(*(it+1));
            for(vector<Point*>::iterator it=SMALL.begin(); it!=SMALL.end(); it+=2)
            {
                candidates.push_back(*it);
                candidates.push_back(*(it+1));
            }
        }

        //10.
        else if(pk->x > a){
            for(vector<Point*>::iterator it=SMALL.begin(); it!=SMALL.end(); it+=2)
                candidates.push_back(*it);
            for(vector<Point*>::iterator it=EQUAL.begin(); it!=EQUAL.end(); it+=2)
                candidates.push_back(*it);
            for(vector<Point*>::iterator it=LARGE.begin(); it!=LARGE.end(); it+=2)
            {
                candidates.push_back(*it);
                candidates.push_back(*(it+1));
            }
        }
    }
	return lowerBridge(candidates, pl, pr, a);

}

//function to find upper hull
list<Point*> UpperHull(Point* pmin, Point* pmax, vector<Point*> PList){


    list<Point*> upper;
	if(pmin->x == pmax->x && pmin->y == pmax->y){
		upper.push_back(pmin);
		return upper;
	}
	//finding median in O(n)
	int n = PList.size();
	nth_element(PList.begin(), PList.begin() + n/2, PList.end(), Compare);

	Point *pl, *pr;
	vector<Point*> temp=PList;
	upperBridge(temp, &pl, &pr, PList[n/2]->x);
	vector<Point*> Tleft = divide(pmin, pl, PList);
	vector<Point*> Tright = divide(pr, pmax, PList);
	upper = UpperHull(pmin, pl, Tleft);
    list<Point*> right=UpperHull(pr, pmax, Tright);
	upper.splice(upper.end(), right );
	return upper;
}


//function to find lower hull
list<Point*> LowerHull(Point* pmin, Point* pmax, vector<Point*> PList){
	list<Point*> lower;
	if(pmin->x == pmax->x && pmin->y == pmax->y){
		lower.push_back(pmin);
		return lower;
	}

    //finding median in O(n)
	int n = PList.size();
	nth_element(PList.begin(), PList.begin() + n/2, PList.end(), Compare);
	Point *pl, *pr;
    vector<Point*> temp=PList;
	lowerBridge(temp, &pl, &pr, PList[n/2]->x);
	vector<Point*> Tleft = divide(pl, pmin, PList);
	vector<Point*> Tright = divide(pmax, pr, PList);
	lower = LowerHull(pr, pmax, Tright);
	list<Point*> left =LowerHull(pmin, pl, Tleft);
    lower.splice(lower.end(), left);
	return lower;
}


vector<Point*> Kirkpatrick::kirkpatrick(vector<Point> &pts){
    Hull.clear();

	Point   *Pumin, *Pumax, *Plmin, *Plmax; //boundary points
	vector<Point*> PList;

	//get boundary points
	findpmin(pts, &Pumin, &Pumax, &Plmin, &Plmax);

	//creating list of pointers
    for(vector<Point>::iterator it=pts.begin(); it!=pts.end(); ++it)
        if(it->x > Pumin->x && it->x < Pumax->x)
            PList.push_back(&(*it));

    //get upper hull
    PList.push_back(Pumin);
    PList.push_back(Pumax);
	list<Point*> upper = UpperHull(Pumin, Pumax, PList);

	PList.pop_back();
	PList.pop_back();

	//get lower hull
	PList.push_back(Plmin);
	PList.push_back(Plmax);
	list<Point*> lower = LowerHull(Plmin, Plmax, PList);

	//remove repetition
	if(Pumin->y==Plmin->y){
		lower.pop_back();
	}
	if(Pumax->y==Plmax->y){
		lower.pop_front();
	}

	//merge upper and lower hulls
	upper.splice(upper.end(), lower);

	//validity check
    if(upper.size()<=2)
    {
        cout<<"Convex hull not possible";
        PList.clear();
        return PList;
    }

    //hull vector for uniformity
    for(list<Point*>::iterator it=upper.begin();it!=upper.end();++it)
        Hull.push_back(*it);

    return Hull;

}
