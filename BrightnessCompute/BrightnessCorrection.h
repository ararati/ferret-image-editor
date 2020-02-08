#ifndef BRIGHNESSCORRECTION_H
#define BRIGHNESSCORRECTION_H

#include "BrightnessCompute.h"

#include <image.h>



class BrightnessCorrection : public BrightnessCompute
{
public:
    static void process(Image* original, Image* image, int brightness);
};

#endif // BRIGHNESSCORRECTION_H
