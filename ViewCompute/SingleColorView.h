#ifndef SINGLECOLORVIEW_H
#define SINGLECOLORVIEW_H

#include "Filter.h"

#include <Image.h>

class SingleColorView  : protected Filter
{
public:
    static void process(Image *originalImg, Image *processImg, int colorIndex=0);
};

#endif // SINGLECOLORVIEW_H
