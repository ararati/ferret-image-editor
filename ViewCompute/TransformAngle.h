#ifndef TRANSFORMANGLE_H
#define TRANSFORMANGLE_H

#include <image.h>



class TransformAngle
{
public:
    static void rotateLeft(Image* original, Image* image);
    static void rotateRight(Image *original, Image *processImg);
};

#endif // TRANSFORMANGLE_H
