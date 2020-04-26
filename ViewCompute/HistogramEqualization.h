#ifndef HISTOGRAMEQUALIZATION_H
#define HISTOGRAMEQUALIZATION_H

#include "Filter.h"
#include <Image.h>

class HistogramEqualization  : protected Filter
{
public:
    HistogramEqualization();
    static void process(Image *original, Image *processing);
    static QVector<double> bwBrightnessData(Image* img);
    static QVector<double> bwNormalization(Image *img);
};

#endif // HISTOGRAMEQUALIZATION_H
