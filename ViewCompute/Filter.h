#ifndef FILTER_H
#define FILTER_H

#include <image.h>



class Filter
{
public:
    static void revertBorders(Image *original, Image *processed, int size);
};

#endif // FILTER_H
