#include "MaskFilter.h"
#include <cstdlib>

void MaskFilter::proccess(Image *original, Image *processing, float mask[3][3], double factor, double bias)
{
    int maskSize = 3;
    int height = processing->height(), width = processing->width();
    uint maskCeils = maskSize*maskSize;
    QRgb tmpPx;

    float tRed, tGreen, tBlue, maskMeed = 1, tmpMaskSize;
    for(int x = 1; x < width-1; x++)
    {
        for(int y = 1; y < height-1; y++)
        {
            tRed = 0; tGreen = 0; tBlue = 0;
            tmpMaskSize = maskCeils;
            for(int r = 0; r < maskSize; r++)
            {
                for(int k = 0; k < maskSize; k++)
                {
                    if(x-(maskMeed-k) < 0 || y-(maskMeed-r) < 0 || y-(maskMeed-r) >= height || x-(maskMeed-k) >= width) {
                        tmpMaskSize--;
                        continue;
                    }

                    tmpPx = original->pixel(x-(1-r), y-(1-k));
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
