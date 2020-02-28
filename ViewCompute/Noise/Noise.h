#ifndef NOISE_H
#define NOISE_H

#include <image.h>



class Noise
{
public:
    static void proccess(Image *original, Image *processed, unsigned int countWhite, unsigned int countBlack);
};

#endif // NOISE_H
