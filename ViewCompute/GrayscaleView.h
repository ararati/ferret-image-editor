#ifndef GRAYSCALEVIEW_H
#define GRAYSCALEVIEW_H

#include "Filter.h"
#include <Image.h>

class GrayscaleView  : protected Filter
{
public:
    static void process(Image *originalImg, Image *processImg);
};

#endif // GRAYSCALEVIEW_H
