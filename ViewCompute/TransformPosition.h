#ifndef TRANSFORMPOSITION_H
#define TRANSFORMPOSITION_H

#include <image.h>



class TransformPosition
{
public:
    static void transformX(Image* original, Image* image, int step);
    static void transformY(Image *original, Image *processImg, int step);
};

#endif // TRANSFORMPOSITION_H
