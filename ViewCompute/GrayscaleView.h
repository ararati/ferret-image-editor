#ifndef GRAYSCALE_H
#define GRAYSCALE_H

#include <image.h>



class GrayscaleView
{
public:
    static void process(Image *originalImg, Image *processImg);
};

#endif // GRAYSCALE_H
