#include "BlurGaus.h"

void BlurGaus::proccess(Image *original, Image *processing, unsigned int maskSize)
{
    float mask[5][5];

    mask[0][0] = mask[4][0] = mask[0][4] = mask[4][4] = 0.000789f;
    mask[0][1] = mask[0][3] = mask[1][0] = mask[1][4] = mask[3][0] = mask[3][4] = mask[4][1] = mask[4][3] = 0.006581f;
    mask[0][2] = mask[2][0] = mask[2][4] = mask[4][2] = 0.013347f;
    mask[1][1] = mask[1][3] = mask[3][1] = mask[3][3] = 0.054901f;
    mask[1][2] = mask[2][1] = mask[2][3] = mask[3][2] = 0.111345f;
    mask[2][2] = 0.225821f;


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
                    tRed += mask[r][k] * qRed(tmpPx);
                    tGreen += mask[r][k] * qGreen(tmpPx);
                    tBlue += mask[r][k] * qBlue(tmpPx);
                }
            }
            processing->setPixel(x, y, qRgb((unsigned char)(tRed), (unsigned char)(tGreen), (unsigned char)(tBlue)));
        }
    }
}
