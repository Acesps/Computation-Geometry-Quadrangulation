#ifndef VISUALIZE_H
#define VISUALIZE_H

#include <opencv/cv.h>
#include "DCEL.h"

namespace Render
{

static void draw(CvMat* canvas, const DCEL& dcel);

}

#endif // VISUALIZE_H 
