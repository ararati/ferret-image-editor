#ifndef MASKFILTER_H
#define MASKFILTER_H

#include "Filter.h"
#include <Image.h>

class MaskFilter  : protected Filter
{
public:
    static void proccess(Image *original, Image *processed, int maskSize, float mask[31][31], double factor = 1., double bias = 1.);
};

#endif // MASKFILTER_H
