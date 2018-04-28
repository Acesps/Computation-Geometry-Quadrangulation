#ifndef QUADRANGULATE


#define QUADRANGULATE
#include "Point.h"
#include "Quadrilateral.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;
class Quadrangulate
{

    public:

        Quadrangulate();
        virtual ~Quadrangulate();
        vector<Point*> ConvexSpiral(vector<Point>&);
        void Quadrangulation(vector<Point>&, vector<Quadrilateral>&);
        vector<pair<Point*,Point*> > getDiagonals();

        vector<Point*> Spiral;
    //protected:
        
    private:
};
#endif //QUADRANGULATE