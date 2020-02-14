#include "NegativeView.h"

void NegativeView::process(Image* originalImg, Image* processImg)
{
    uint height = originalImg->height(), width = originalImg->width();
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            QRgb px = originalImg->pixel(x, y);
            processImg->setPixel(x, y, qRgb(255-qRed(px), 255-qGreen(px), 255-qBlue(px)));
        }
    }
}
