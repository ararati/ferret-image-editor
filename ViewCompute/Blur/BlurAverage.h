#ifndef BLURAVERAGE_H
#define BLURAVERAGE_H

#include <image.h>



class BlurAverage
{
public:
    static void proccess(Image *original, Image *processed, unsigned int maskSize);
};

#endif // BLURAVERAGE_H
