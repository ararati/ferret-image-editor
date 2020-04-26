#ifndef BLURAVERAGE_H
#define BLURAVERAGE_H

#include <Image.h>
#include <ViewCompute/Filter.h>


class BlurAverage : protected  Filter
{
public:
    static void proccess(Image *original, Image *processed, unsigned int maskSize);
};

#endif // BLURAVERAGE_H
