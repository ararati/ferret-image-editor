#include "SymmetryTransform.h"
#include <QDebug>

void SymmetryTransform::transformHorizontal(Image *originalImg, Image *processImg)
{
    uint height = processImg->height()-1, width = processImg->width();
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height/2; y++)
        {
            QRgb px = processImg->pixel(x, y);
            processImg->setPixel(x, y, processImg->pixel(x, height-y));
        }
    }
}

void SymmetryTransform::transformVertical(Image *originalImg, Image *processImg)
{
    uint height = processImg->height(), width = processImg->width()-1;
    for(int x = 0; x < width/2; x++)
    {
        for(int y = 0; y < height; y++)
        {

            QRgb px = processImg->pixel(x, y);
            processImg->setPixel(x, y, processImg->pixel(width-x, y));
        }
    }
}
