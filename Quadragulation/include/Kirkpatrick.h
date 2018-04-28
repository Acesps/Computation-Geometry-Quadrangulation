#ifndef KIRKPATRICK_H
#define KIRKPATRICK_H
#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include "Point.h"

class Kirkpatrick
{
    public:
        vector<Point*> kirkpatrick(vector<Point> &);

        Kirkpatrick();
        virtual ~Kirkpatrick();

    protected:
        vector<Point*> Hull;

    private:
};

#endif // KIRKPATRICK_H
