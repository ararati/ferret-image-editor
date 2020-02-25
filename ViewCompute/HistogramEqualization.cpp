#include "HistogramEqualization.h"
#include <QtDebug>

void HistogramEqualization::process(Image* original, Image* processing)
{

}

QVector<double> HistogramEqualization::bwBrightnessData(Image* img) {
    QVector<double> brightness(256);

    for(int i = 0; i < 256; i++)
        brightness[i] = 0;

    for(int y = 0; y < img->height(); y++)
    {
        for(int x = 0; x < img->width(); x++)
        {
            QRgb px = img->pixel(x, y);
            brightness[qRed(px)] += 1;
        }
    }

//    for(int i = 0; i < 256; i++)
//        qInfo() << i << ": " << brightness[i];

//    qInfo() << "Min " << *std::min_element(brightness.constBegin(), brightness.constEnd());
//    qInfo() << "Max " << *std::max_element(brightness.constBegin(), brightness.constEnd());

    return brightness;
}

QVector<double> HistogramEqualization::bwNormalization(Image* img) {
    QVector<double> defaultH = HistogramEqualization::bwBrightnessData(img);
    QVector<double> normalizeH(256);
    QVector<double> cumulatedH(256);


    int pixCount = img->width() * img->height();
    int bins = 256;

    for(int i = 0; i < 256; i++)
        normalizeH[i] = 255.0 *  defaultH[i] / pixCount;

    int t = 0;
    for(int i = 0; i < 256; i++)
        t += normalizeH[i];

    qInfo() << t;

    //Кумулятивная гистограмма
    int sum;
    for(int i = 0; i < bins; i++) {
        sum = 0;
        for(int j = 0; j < i; j++) {
            sum += normalizeH[j];
        }
        cumulatedH[i] = sum + 0.5;
    }

    qInfo() << *std::min_element(cumulatedH.constBegin(), cumulatedH.constEnd());
    qInfo() << *std::max_element(cumulatedH.constBegin(), cumulatedH.constEnd());

    //Нормализация изоображения
    for(int x = 0; x < img->width(); x++)
    {
        for(int y = 0; y < img->height(); y++)
        {
            QRgb px = img->pixel(x, y);
            int grayBrightness  = qRed(img->pixel(x, y));
            int brt = cumulatedH[grayBrightness];
            img->setPixel(x, y, qRgb(brt, brt, brt));
        }
    }

    return normalizeH;
}
