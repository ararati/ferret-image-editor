#include "GrayscaleView.h"


void GrayscaleView::process(Image *originalImg, Image *processImg)
{
    uint height = originalImg->height(), width = originalImg->width();
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            QRgb px = originalImg->pixel(x, y);
            float k = 0.2126 * qRed(px) + 0.7152 * qBlue(px) + 0.0722 * qGreen(px);
            processImg->setPixel(x, y, qRgb(k, k, k));
        }
    }
}
