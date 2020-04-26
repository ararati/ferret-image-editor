#ifndef BLURGAUS_H
#define BLURGAUS_H

#include <Image.h>
#include <ViewCompute/Filter.h>

class BlurGaus  :  protected Filter
{
public:
    static void proccess(Image *original, Image *processed, unsigned int maskSize);
};

#endif // BLURGAUS_H
