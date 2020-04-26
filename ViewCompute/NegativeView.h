#ifndef NEGATIVEVIEW_H
#define NEGATIVEVIEW_H

#include "Filter.h"
#include <Image.h>


class NegativeView  : protected Filter
{
public:
    static void process(Image *originalImg, Image *processImg);
};

#endif // NEGATIVEVIEW_H
