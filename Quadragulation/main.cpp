/*!Introduction
The project implements two essential computational geometry algorithms:
1. Convex Hull
2. Polygon Triangulation

CONVEX HULL
The convex hull (convex envelope or convex closure) of a set X of points in the Euclidean plane is the smallest convex set that contains X. 

We have implemented three convex hull algorithms:
1. Grahams Scan
2. Jarvis Scan
3. Kirkpatrick Seidal

POLYGON TRIANGULATION
Polygon triangulation is the decomposition of a polygonal area (simple polygon) P into a set of triangles i.e., finding a set of triangles with pairwise non-intersecting interiors whose union is P.

Three algorithms have been implement for triangulation of a simple polygon:
1. DCEL data structure to store polygon
2. Partitioning a polygon into y-monotone polygons
3. Triangulating a Y-monotone polygon

*/

#include "triangulation.hpp"
#include "hull.hpp"
#include "Quadrangulation.hpp"
#include <iostream>
#include <condition_variable>

#include <stdio.h>

using namespace std;

int main()
{
	int c1=0;
	while(c1!=3)
    {
        cout<<"\n\n\nMAIN MENU:\n\t 1> Convex Hull \n\t 2> Polygon triangulation\n\t 3> Quadrangulation\n\t4>Exit \n   >> ";
        cin>>c1;

        switch(c1)
        {
        case 1:
            start_hull();
            break;
        case 2:
            start_triangulation();
            break;
        case 3:
            start_Quadrangulation();
            break;
        case 4:
            return 0;
        default:
            cout<<"\nPlease choose a valid option...";
            continue;
        }
    }
    return 0;
}

