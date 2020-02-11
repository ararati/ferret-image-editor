#ifndef BRIGHTNESSVIEW_H
#define BRIGHTNESSVIEW_H

#include <image.h>



class BrightnessView
{
public:
    static void process(Image* original, Image* image, int brightness);
};

#endif // BRIGHTNESSVIEW_H
