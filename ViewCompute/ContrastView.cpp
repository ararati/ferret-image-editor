#include "ContrastView.h"
#include <qdebug.h>

QRgb ContrastView::calculateContrast(QRgb pixel, int min, int max, int bins) {
    QRgb newColor;
    int colorK;
    if (qBlue(pixel) < min) {
        colorK = 0;
    }
    else if (qBlue(pixel) > max) {
        colorK = 255;
    }
    else {
        colorK = (qBlue(pixel) - min) * (bins / (max - min));
    }

    newColor = qRgb(colorK, colorK, colorK);

    return newColor;
}

void ContrastView::processBW(Image *originalImg, Image *processImg, int min, int max)
{
    uint height = originalImg->height(), width = originalImg->width();
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            QRgb pixel = originalImg->pixel(x, y);
            processImg->setPixel(x, y, calculateContrast(pixel, min, max));
        }
    }
}

void ContrastView::processRGB(Image *originalImg, Image *processImg, float C)
{
    uint height = originalImg->height(), width = originalImg->width();
    float factor = (259*(C+255)) / (255*(259-C));
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
                QRgb pixel = originalImg->pixel(x, y);
                processImg->setPixel(x, y, qRgb(
                                            Filter::getValidRgb(factor * (qRed(pixel) -128) + 128),
                                            Filter::getValidRgb(factor * (qGreen(pixel) -128) + 128),
                                            Filter::getValidRgb(factor * (qBlue(pixel) -128) + 128)
                                            )
                                     );
        }
    }
}

