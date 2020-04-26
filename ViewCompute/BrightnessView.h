#ifndef BRIGHTNESSVIEW_H
#define BRIGHTNESSVIEW_H

#include "Filter.h"
#include <Image.h>

class BrightnessView  : protected Filter
{
public:
    static void process(Image* original, Image* image, int brightness);
};

#endif // BRIGHTNESSVIEW_H
