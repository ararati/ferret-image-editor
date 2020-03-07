#include "BinaryView.h"
#include "GrayscaleView.h"
#include <QtDebug>

void BinaryView::process(Image *original, Image *processed, int treshold)
{
    uint height = processed->height(), width = processed->width();
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            QRgb px = original->pixel(x, y);
            int bin = (qBlue(px) >= treshold) ? 255 : 0;
            processed->setPixel(x, y, qRgb(bin, bin, bin));
        }
    }
}

void BinaryView::binaryColor(Image *original, Image *processed, int rT, int gT, int  bT)
{
    uint height = processed->height(), width = processed->width(), r, g, b;
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            QRgb px = original->pixel(x, y);
            r = (qRed(px) >= rT) ? 255 : 0;
            g = (qGreen(px) >= gT) ? 255 : 0;
            b = (qBlue(px) >= bT) ? 255 : 0;

            processed->setPixel(x, y, qRgb(r, g, b));
        }
    }
}
