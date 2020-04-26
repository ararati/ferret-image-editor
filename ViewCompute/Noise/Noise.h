#ifndef NOISE_H
#define NOISE_H

#include <Image.h>
#include <ViewCompute/Filter.h>

class Noise : protected Filter
{
public:
    static void proccess(Image *original, Image *processed, unsigned int countWhite, unsigned int countBlack);
    static void bipolar(Image *original, Image *processing, unsigned int count);
};

#endif // NOISE_H
