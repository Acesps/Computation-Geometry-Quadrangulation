#ifndef JARVIS_H
#define JARVIS_H
#include <iostream>
#include <vector>
#include "Point.h"


class Jarvis
{
    public:
        vector<Point*> jarvis(vector<Point> &);

        Jarvis();
        virtual ~Jarvis();

    protected:
        vector<Point*> Hull;

    private:
};

#endif // JARVIS_H
