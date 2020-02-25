#ifndef HISTOGRAMEQUALIZATION_H
#define HISTOGRAMEQUALIZATION_H

#include <image.h>



class HistogramEqualization
{
public:
    HistogramEqualization();
    static void process(Image *original, Image *processing);
    static QVector<double> bwBrightnessData(Image* img);
    static QVector<double> bwNormalization(Image *img);
};

#endif // HISTOGRAMEQUALIZATION_H
