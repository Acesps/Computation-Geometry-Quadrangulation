#include <iostream>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <opencv2/opencv.hpp>

#include "Point.h"
#include "DCEL.h"
#include "Sweepline.h"
#include "Vertex.h"
#include "Window.h"

#include <stdio.h>

using namespace std;



int start_triangulation()
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

    DCEL dcel;    
    SweepLine l;
    vector<Triangle> t_list;

    cout<<"\n\nRunning Polygon Triangulation:"<<endl;
    cout<<"\nNumber of points: "<<info.points.size()<<endl<<endl;
    clock_t t=clock();
    l.triangulate(info.points, t_list, dcel);
    t=clock()-t;

    cout<<"\n\nTriangles:"<<endl;
    int i=1;
    for (auto t : t_list)
    {
        cout<<i++<<">\t("<<t.point1.x<<","<< t.point1.y<<")\t("<<t.point2.x<<","<< t.point2.y<<")\t("<<t.point3.x<< t.point3.y<<")"<<endl;
        cv::Point v3[1][3];
        v3[0][0] = cv::Point(t.point1.x, t.point1.y);
        v3[0][1] = cv::Point(t.point2.x, t.point2.y);
        v3[0][2] = cv::Point(t.point3.x, t.point3.y);
        
        const cv::Point* ppt[1] = { v3[0] };
        int npt[] = { 3 };

        cv::fillPoly(info.canvas, ppt, npt, 1, cv::Scalar(rng.next() % 200 + 55, rng.next() % 200 + 55, rng.next() % 200 + 55), 8);
    }

    cout << "\nTime taken by Algorithm:" << t * 1000.0 / CLOCKS_PER_SEC << " ms"<<endl;

    // Visualization
    for (auto point : info.points)
    {
        circle(info.canvas, cv::Point2i(point.x, point.y), 1, cv::Scalar(200,100,200), 2);
    }
    imshow("Result", info.canvas);

    cv::waitKey();
    return 0;
}
