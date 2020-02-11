#ifndef BINARYVIEW_H
#define BINARYVIEW_H

#include <image.h>



class BinaryView
{
public:
    static void process(Image* original, Image* image, int treshold);
};

#endif // BINARYVIEW_H
