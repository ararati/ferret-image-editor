#ifndef MASKFILTER_H
#define MASKFILTER_H

#include <image.h>



class MaskFilter
{
public:
    static void proccess(Image *original, Image *processed, int maskSize, float mask[31][31], double factor, double bias);
};

#endif // MASKFILTER_H
