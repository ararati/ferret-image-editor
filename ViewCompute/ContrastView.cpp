#include "ContrastView.h"

#include <qdebug.h>
#include <Helper.h>

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
//            Vec3b pixel = originalImg->getCvImg().at<Vec3b>(row, col);
//            processImg->getCvImg().at<Vec3b>(row, col) = calculateContrast(pixel, min, max);
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
                                            Helper::valid_rgb(factor * (qRed(pixel) -128) + 128),
                                            Helper::valid_rgb(factor * (qGreen(pixel) -128) + 128),
                                            Helper::valid_rgb(factor * (qBlue(pixel) -128) + 128)
                                            )
                                     );
                //processImg->getCvImg().at<Vec3b>(row, col)[i] = saturate_cast<uchar>(C * (originalImg->getCvImg().at<Vec3b>(row,col)[i] + 1));
//                processImg->getCvImg().at<Vec3b>(row, col)[i] = saturate_cast<uchar>(factor * (originalImg->getCvImg().at<Vec3b>(row,col)[i] - 128) + 128);
            //Vec3b pixel = originalImg->getCvImg().at<Vec3b>(row, col);
            //processImg->getCvImg().at<Vec3b>(row, col) = calculateContrast(pixel, min, max);
        }
    }
}

