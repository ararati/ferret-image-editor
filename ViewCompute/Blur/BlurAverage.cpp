#include "BlurAverage.h"

#include <Helper.h>
#include <qgenericmatrix.h>

void BlurAverage::proccess(Image *original, Image *processing, unsigned int maskSize)
{
    int height = processing->height(), width = processing->width();
    uint maskCeils = maskSize*maskSize;
    QRgb tmpPx;

    int tRed, tGreen, tBlue, maskMeed = maskSize/2, tmpMaskSize;
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
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

                    tmpPx = original->pixel(x-(maskMeed-k), y-(maskMeed-r));
                    tRed +=   qRed(tmpPx);
                    tGreen +=   qGreen(tmpPx);
                    tBlue +=   qBlue(tmpPx);
                }
            }
            processing->setPixel(x, y, qRgb((unsigned char)(tRed/tmpMaskSize), (unsigned char)(tGreen/tmpMaskSize), (unsigned char)(tBlue/tmpMaskSize)));
        }
    }
}
