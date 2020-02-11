#ifndef SINGLECOLOR_H
#define SINGLECOLOR_H

#include <image.h>



class SingleColorView
{
public:
    static void process(Image *originalImg, Image *processImg, int colorIndex=0);
};

#endif // SINGLECOLOR_H
