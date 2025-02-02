#ifndef CONTRASTVIEW_H
#define CONTRASTVIEW_H

#include "Filter.h"
#include <Image.h>

class ContrastView  : protected Filter
{
public:
    static void processBW(Image *originalImg, Image *processImg, int min, int max);
    static void processRGB(Image *originalImg, Image *processImg, float C);
    static QRgb calculateContrast(QRgb pixel, int min, int max, int bins=256);
};

#endif // CONTRASTVIEW_H
