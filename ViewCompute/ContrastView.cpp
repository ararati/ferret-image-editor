#include "ContrastView.h"

#include <qdebug.h>
#include <Helper.h>

Vec3b ContrastView::calculateContrast(Vec3b pixel, int min, int max, int bins) {
    Vec3b newColor;

    int colorK;
    if (pixel[0] < min) {
        colorK = 0;
    }
    else if (pixel[0] > max) {
        colorK = 255;
    }
    else {
        colorK = (pixel[0] - min) * (bins / (max - min));
    }

    newColor = Vec3b(colorK, colorK, colorK);

    return newColor;
}

void ContrastView::processBW(Image *originalImg, Image *processImg, int min, int max)
{
    uint height = originalImg->getHeight(), width = originalImg->getWidth();
    for(int row = 0; row < height; row++)
    {
        for(int col = 0; col < width; col++)
        {
            Vec3b pixel = originalImg->getCvImg().at<Vec3b>(row, col);
            processImg->getCvImg().at<Vec3b>(row, col) = calculateContrast(pixel, min, max);
        }
    }
}

void ContrastView::processRGB(Image *originalImg, Image *processImg, float C)
{
    uint height = originalImg->getHeight(), width = originalImg->getWidth();
    float factor = (259*(C+255)) / (255*(259-C));
    for(int row = 0; row < height; row++)
    {
        for(int col = 0; col < width; col++)
        {
            for(int i = 0; i < 3; i++) {
                //processImg->getCvImg().at<Vec3b>(row, col)[i] = saturate_cast<uchar>(C * (originalImg->getCvImg().at<Vec3b>(row,col)[i] + 1));
                processImg->getCvImg().at<Vec3b>(row, col)[i] = saturate_cast<uchar>(factor * (originalImg->getCvImg().at<Vec3b>(row,col)[i] - 128) + 128);
            }
            //Vec3b pixel = originalImg->getCvImg().at<Vec3b>(row, col);
            //processImg->getCvImg().at<Vec3b>(row, col) = calculateContrast(pixel, min, max);
        }
    }
}

