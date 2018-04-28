#ifndef GRAHAMS_H
#define GRAHAMS_H
#include <iostream>
#include <algorithm>
#include <vector>
#include "Point.h"


class Grahams
{
    public:
        vector<Point*> grahams(vector<Point> &);

        Grahams();
        virtual ~Grahams();

    protected:
        vector<Point*> Hull;
        vector<Point*> PList;

        void findp0();

    private:
};

#endif // GRAHAM_H
