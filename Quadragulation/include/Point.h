#ifndef POINT_H
#define POINT_H

using namespace std;
class Point
{
    public:
        double x,y;

        int angle(Point, Point);
        double dis (Point);
        double slope (Point);
        double intersect(double);
        double  cross(const Point&) const;
        Point to(const Point&) const;

        bool isBelow(const Point&) const;

        static bool compfunc(Point i, Point j)
        {
            return (i.y>j.y || (i.y == j.y && i.x < j.x));
        }
        bool operator==(const Point &right) const
        {
            return ((y==right.y) && (x == right.x));
        }
        bool operator<(const Point &j)
        {
            return (y>j.y || (y == j.y && x < j.x));
        }
        
Point();
        Point(double, double);
        virtual ~Point();

    protected:

    private:
};

#endif // POINT_H
