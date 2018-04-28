#include <iostream>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <opencv2/opencv.hpp>

#include "Point.h"
#include "Window.h"
#include "Grahams.h"
#include "Jarvis.h"
#include "Kirkpatrick.h"

#include <stdio.h>

using namespace std;



void start_anim(int ch)
{
    cv::RNG rng;
    InputInfo info;
    info.canvas = cv::Mat(WIN_HEIGHT, WIN_WIDTH, CV_8UC3);

    imshow("Result", info.canvas);
    cv::setMouseCallback("Result", mouse_handler, &info);

    while (control)
    {
        cv::waitKey(10);
    }

    Grahams g;
    Jarvis j;
    Kirkpatrick k;
    vector<Point*> polygon;
    DCEL dcel;    
    SweepLine l;
    vector<Triangle> t_list;

    cout<<"\nNumber of points: "<<info.points.size()<<endl;

    clock_t t=clock();

    switch(ch)
    {
    case 1:
        polygon = g.grahams(info.points);
        break;
    case 2:
        polygon = j.jarvis(info.points);
        break;
    case 3:
        polygon = k.kirkpatrick(info.points);
        break;
    }

    t=clock()-t;
    cout<<"\nPoints on hull : "<<polygon.size();
    cout <<"\n\nConvex Hull\n";
    for(vector<Point*>::iterator it=polygon.begin(); it!=polygon.end(); ++it)
        cout<<(*it)->x<<"\t"<<(*it)->y<<endl;
    cout << "\nTime taken by Algorithm:" << t * 1000.0 / CLOCKS_PER_SEC << " ms"<<endl;

    cv::Point v3[1][polygon.size()];
    int i=0;
    for (auto p : polygon)
        v3[0][i++] = cv::Point(p->x, p->y);

    const cv::Point* ppt[1] = { v3[0] };
    int npt[] = { polygon.size() };

    cv::fillPoly(info.canvas, ppt, npt, 1, cv::Scalar(0, 200, 200), 8);
    cv::polylines(info.canvas, ppt, npt, 1, true, cv::Scalar(255,255,0));
    // Visualization
    for (auto point : info.points)
    {
        circle(info.canvas, cv::Point2i(point.x, point.y), 1, cv::Scalar(100,0,100), 2);
    }
    imshow("Result", info.canvas);

    cv::waitKey();
}
int start_hull()
{
    int c=0;
    cout<<"\n\nALGORITHM MENU:\n\t 1> Graham's Algorithm \n\t 2> Jarvis March from stdin\n\t 3> Kirkpatrick-Seidel Algorithm \n\t 4> Return to Main Menu\n   >> ";
    cin>>c;

    switch(c)
    {
    case 1:
        cout<<"\n\nRunning Graham's Algorithm:"<<endl;
        start_anim(c);
        break;
    case 2:
        cout<<"\n\nRunning Jarvis Algorithm:"<<endl;
        start_anim(c);
        break;
    case 3:
        cout<<"\n\nRunning kirkpatrick-seidal Algorithm:"<<endl;
        start_anim(c);
        break;
    // case 4:
    //     for(int i=0;i<3;++i)
    //         if(B.test(i))
    //         {
    //             cout<<"\n\nConvex Hull for Algorithm "<<i+1<<endl;
    //             for(vector<Point*>::iterator it=Hull[i].begin(); it!=Hull[i].end(); ++it)
    //                 cout<<(*it)->x<<"\t"<<(*it)->y<<endl;
    //         }
    //     getch();
    //     break;
    }

    return 0;
}
