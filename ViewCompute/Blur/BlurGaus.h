#ifndef BLURGAUS_H
#define BLURGAUS_H

#include <image.h>



class BlurGaus
{
public:
    static void proccess(Image *original, Image *processed, unsigned int maskSize);
};

#endif // BLURGAUS_H
