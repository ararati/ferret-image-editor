#ifndef BINARYVIEW_H
#define BINARYVIEW_H

#include <image.h>



class BinaryView
{
public:
    static void process(Image* original, Image* image, int treshold);
    static void binaryColor(Image *original, Image *processed, int rT, int gT, int bT);
};

#endif // BINARYVIEW_H
