#include "Quadrangulate.h"

Quadrangulate::Quadrangulate(){
	//ctor
}
Quadrangulate::~Quadrangulate(){
	//dtor
}

ostream& operator <<(ostream& o,vector<Point*> a){
	size_t n= a.size();
	for(size_t i=0;i<n;i++){
		o<<(a[i])->x<<" "<<(a[i])->y<<"\n";
	}
	o<<"\n";
	return o;
}

ostream& operator <<(ostream& o,vector<pair<Point*,Point*> > a){
    size_t n= a.size();
    for(size_t i=0;i<n;i++){
        o<<(a[i].first)->x<<" "<<(a[i].first)->y<<"),("<<(a[i].second)->x<<" "<<(a[i].second)->y<<"\n";
    }
    o<<"\n";
    return o;
}

int Ph_index;
Point * Pzero;
vector<Point*> Hull;
vector<Point*> PList;
vector<Point*> Resedue;
Point Steiner_point;

//comparison function for sorting
bool PCompare1(Point* p1, Point* p2)
{
    int C = Pzero->angle(*p1, *p2);
    if(C==0)
        return Pzero->dis(*p1) <= Pzero->dis(*p2) ;
    return C==1;
}

//Finding leftmost lowermost point
void findp0()
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
    Pzero=(*p0);
    PList.erase(p0);
}

vector<Point*> grahams(vector<Point*> PList)
{
    Hull.clear();
    Resedue.clear();
    
    
    //sort based on angles with Pzero
    sort(PList.begin(),PList.end(),PCompare1);

    //remove points at same angle from Pzero
    for(vector<Point*>::iterator it=PList.begin()+1; it!=PList.end(); ++it)
    {
        if(Pzero->angle(**(it-1),**it)==0)
        {   Resedue.push_back(*(it-1));
            PList.erase(it-1);
            --it;
        }
    }
    //validity check
    if(PList.size() < 2)
    {   Hull.push_back(Pzero);
    	Hull.insert(Hull.end(),PList.begin(),PList.end());
        PList.clear();
        return PList;
    }
    //check for anti-clockwise turn
    Hull.push_back(Pzero);
    Hull.push_back(PList[0]);
    Hull.push_back(PList[1]);
    for(vector<Point*>::iterator it=PList.begin()+2; it!=PList.end(); ++it)
    {
        while(Hull[Hull.size()-2]->angle(*Hull.back(),**it) != 1)
        {
            Resedue.push_back(Hull.back() );
            Hull.pop_back();
        }   

        Hull.push_back(*it);
    }
    return Hull;

}

vector<Point*> Quadrangulate::ConvexSpiral(vector<Point> &pts){
	Spiral.clear();
	PList.clear();
	for(unsigned int i=0; i<pts.size(); ++i)
        PList.push_back(&pts[i]);
    findp0();
    grahams(PList);
	if(Hull.size()%2){
        Steiner_point= Point((Hull[0]->x + Hull.back()->x)/2 - 5,(Hull[0]->y + Hull.back()->y)/2 - 5);
        Spiral.push_back(&Steiner_point); 
    }
    Spiral.insert(Spiral.end(),Hull.begin(),Hull.end());
    //initializing Ph;
    cout<<"first hull\n";
    cout<<Spiral;
    Ph_index = Spiral.size() - 1;
    cout<<"p0= "<<Spiral[0]->x<<"ph= "<<Spiral[Ph_index]->x<<endl;
    while(Resedue.size()){
        Pzero = Hull.back();
        grahams(Resedue);
        Spiral.insert(Spiral.end(),Hull.begin() + 1,Hull.end());
    }
	return Spiral;
}

vector<pair<Point*,Point*> > Quadrangulate::getDiagonals(){
    vector<pair<Point*,Point*> > diagonals;
    cout<<Ph_index<<"Ph_index in diagonals\n";
    cout<<Spiral;
    diagonals.push_back(make_pair(Spiral[0],Spiral[Ph_index]));
    //pointer for C0
    auto it_i = Spiral.begin();
    if(Ph_index < Spiral.size() - 1 )
    {//pointer for Ci
        auto it_j = Spiral.begin() + Ph_index;
        //for region P0
        while(it_j != Spiral.begin() + Spiral.size() - 1){
            cout<<"jage raho\n";
            if( (*(it_j+1))->angle(**(it_j),**(it_i+1)) ==1 ){
                it_i++;
            }
            else{
                it_j++;
            }
            diagonals.push_back(make_pair(*it_i,*it_j));
        }
    }
    //for region P1
    auto final = Spiral.begin() + Spiral.size() - 2; 
    while(it_i != final){
        it_i++;
        diagonals.push_back(make_pair(*it_i,Spiral.back()));
    }
    return diagonals;
}

void Quadrangulate::Quadrangulation(vector<Point>& pts, vector<Quadrilateral>& q_list){
	ConvexSpiral(pts);
	vector<pair<Point*,Point*> > diagonals = getDiagonals();
    cout<<Spiral.size()<<" spiral ka size"<<endl;
    cout<<Spiral;
    cout<<"yaha ho raha hai jadu\n";
    cout<<diagonals.size()<<endl;
    cout<<diagonals;
    cout<<Ph_index<<" Ph_index"<<endl;
    for(int i = 0 ;i<diagonals.size()-2;i+=2){
        PList.clear();
        for(int j =0 ;j<3;j++){
            PList.push_back(diagonals[i+j].first);    
            PList.push_back(diagonals[i+j].second);    
        }
        if(PList.size()!= 6){
            cout<<"NOOOOOOOO!, Size of set is:"<<PList.size();
        }
        if(*PList[1]==*PList[3]){
            PList.erase(PList.begin() + 1);
            if(*PList[2]==*PList[4]){
                PList.erase(PList.begin() + 2);
                cout<<"case 1\\|/"<<endl;
            }
            else{
                PList.erase(PList.begin() + 3);
                cout<<"case 2\\|\\"<<endl;
                swap(PList[2],PList[3]);
            }
        }
        if(*PList[0]==*PList[2]){
            PList.erase(PList.begin() + 2);
            if(*PList[0]==*PList[3]){
                cout<<"case 4|\\\\"<<endl;
                PList.erase(PList.begin() + 3);
            }
            else{
                cout<<"case 3|\\/"<<endl;
                PList.erase(PList.begin() + 4);
            }
        }
        //sort(PList.begin(),PList.end());
        /*for(int j=0;j<PList.size()-1;j++){
            if(*PList[j]==*PList[j+1]){
                PList.erase(PList.begin()+ j+1);
                j--;
            }
        }*/

        /*if(PList[0]->angle(*PList[1],*PList[2]) != PList[1]->angle(*PList[2],*PList[3])){
            Point* temp= PList[2];
            PList[2]=PList[3];
            PList[3]=temp;
        }
        if(PList[1]->angle(*PList[2],*PList[3]) != PList[2]->angle(*PList[3],*PList[0])){
            Point* temp= PList[3];
            PList[3]=PList[0];
            PList[0]=temp;
        }
        if(PList[2]->angle(*PList[3],*PList[0]) != PList[3]->angle(*PList[0],*PList[1])){
            Point* temp= PList[0];
            PList[0]=PList[1];
            PList[1]=temp;
        }if(PList[3]->angle(*PList[0],*PList[1]) != PList[0]->angle(*PList[1],*PList[2])){
            Point* temp= PList[1];
            PList[1]=PList[2];
            PList[2]=temp;
        }*/
        cout<<PList;
        q_list.push_back(Quadrilateral(*PList[0],*PList[1],*PList[2],*PList[3]));
        cout<<"diagonal deleted && quadrilateral added"<<endl;
    }
    cout<<q_list.size()<< " Qlisst ka size"<<endl;
    return;
}
