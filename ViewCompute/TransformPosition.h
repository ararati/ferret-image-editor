#ifndef TRANSFORMPOSITION_H
#define TRANSFORMPOSITION_H

#include "Filter.h"

#include <Image.h>

class TransformPosition : protected Filter
{
public:
    static void transformX(Image* original, Image* image, int step);
    static void transformY(Image *original, Image *processImg, int step);
};

#endif // TRANSFORMPOSITION_H
