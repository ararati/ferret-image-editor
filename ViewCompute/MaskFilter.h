#ifndef MASKFILTER_H
#define MASKFILTER_H

#include <image.h>



class MaskFilter
{
public:
    static void proccess(Image *original, Image *processed, float mask[3][3], double factor, double bias);
};

#endif // MASKFILTER_H
