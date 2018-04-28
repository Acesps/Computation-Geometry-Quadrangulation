#ifndef WINDOW_H
#define WINDOW_H

#include <iomanip>
#include <opencv2/opencv.hpp>

#include <vector>

#include "Point.h"
const uint WIN_WIDTH  = 512;
const uint WIN_HEIGHT = 512;


bool control=true;


typedef struct
{
    int max_points_num;
    int curr_points_num;
    vector<Point> points;
    cv::Mat canvas;

    bool get_point = false;
    Point point_locate;
} InputInfo;


static void mouse_handler(int event, int x, int y, int flags, void* param)
{
    InputInfo* p_info = static_cast<InputInfo*>(param);
    if (event == CV_EVENT_LBUTTONDOWN)
    {
        p_info->points.push_back(Point(x, y));
        circle(p_info->canvas, cv::Point2i(x, y), 1, cv::Scalar(100, 200, 100), 2);
        imshow("Result", p_info->canvas);
        cout << setw(10) << "x = " << x << "\ty = " << y << endl;
    }
    else if (event == CV_EVENT_RBUTTONDOWN )
    {
        control=false;
    }
}

#endif // WINDOW_H