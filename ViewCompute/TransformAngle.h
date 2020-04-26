#ifndef TRANSFORMANGLE_H
#define TRANSFORMANGLE_H

#include "Filter.h"

#include <Image.h>

class TransformAngle  : protected Filter
{
public:
    static void rotateLeft(Image* original, Image* image);
    static void rotateRight(Image *original, Image *processImg);
};

#endif // TRANSFORMANGLE_H
