#include "MaskFilter.h"
#include <cstdlib>
#include <QtDebug>

void MaskFilter::proccess(Image *original, Image *processing, int maskSize, float mask[31][31], double factor, double bias)
{
    int maskMeed = maskSize/2, tx = 0, ty = 0;
    int height = processing->height(), width = processing->width();
    uint maskCeils = maskSize*maskSize;
    QRgb tmpPx;

    //Without borders
    float tRed, tGreen, tBlue, tmpMaskSize;
    for(int x = 0; x < width; x++)
    {
        tx = (x == 0) ? maskMeed : (x == width-1) ? -maskMeed : 0;
        for(int y = 0; y < height; y++)
        {
            tRed = 0; tGreen = 0; tBlue = 0;
            tmpMaskSize = maskCeils;
            ty = (y == 0) ? maskMeed : (y == height-1) ? -maskMeed : 0;
            for(int r = 0; r < maskSize; r++)
            {
                for(int k = 0; k < maskSize; k++)
                {

                    if(x-(maskMeed-k) < 0 || y-(maskMeed-r) < 0 || y-(maskMeed-r) >= height || x-(maskMeed-k) >= width) {
                        tmpMaskSize--;
                        continue;
                    }

                    tx = ty = 0;
                    tmpPx = original->pixel(x-(maskMeed-k)+tx, y-(maskMeed-r)+ty);
                    tRed +=    mask[k][r] * qRed(tmpPx);
                    tGreen +=   mask[k][r] * qGreen(tmpPx);
                    tBlue +=   mask[k][r] * qBlue(tmpPx);
                }
            }

            tRed = min(max(int(factor * tRed + bias), 0), 255);
            tGreen = min(max(int(factor * tGreen + bias), 0), 255);
            tBlue = min(max(int(factor * tBlue + bias), 0), 255);
            processing->setPixel(x, y, qRgb(tRed, tGreen, tBlue));
        }
    }
}
