#ifndef SINGLECOLORVIEW_H
#define SINGLECOLORVIEW_H

#include <image.h>



class SingleColorView
{
public:
    static void process(Image *originalImg, Image *processImg, int colorIndex=0);
};

#endif // SINGLECOLORVIEW_H
