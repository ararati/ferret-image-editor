#include "BlurMedian.h"
#include <QtDebug>

void BlurMedian::square(Image *original, Image *processing)
{
    int height = processing->height(), width = processing->width();
    uint squareSize = 3;
    int squareCells = squareSize*squareSize;
    bool isEven = (squareCells % 2) == 0;
    QRgb tmpPx;
    int r, g, b, maskMeed = squareSize/2, i = 0, tx = 0, ty = 0;
    int medianR[squareCells], medianG[squareCells],  medianB[squareCells];

    for(int x = 0; x < width; x++)
    {
        tx = (x == 0) ? maskMeed : (x == width-1) ? -maskMeed : 0;
        for(int y = 0; y < height; y++)
        {
            i = 0;
            ty = (y == 0) ? maskMeed : (y == height-1) ? -maskMeed : 0;
            for(int r = 0; r < squareSize; r++)
            {
                for(int k = 0; k < squareSize; k++)
                {
                    tmpPx = original->pixel(x-(maskMeed-k)+tx, y-(maskMeed-r)+ty);
                    medianR[i] = qRed(tmpPx);
                    medianG[i] = qGreen(tmpPx);
                    medianB[i] = qBlue(tmpPx);
                    i++;
                }
            }


            std::sort(medianR, medianR+squareCells);
            std::sort(medianG, medianG+squareCells);
            std::sort(medianB, medianB+squareCells);

            r = (isEven) ? (medianR[squareCells/2] + medianR[squareCells/2 -1]) / 2 : medianR[squareCells/2];
            g = (isEven) ? (medianG[squareCells/2] + medianG[squareCells/2 -1]) / 2 : medianG[squareCells/2];
            b = (isEven) ? (medianB[squareCells/2] + medianB[squareCells/2 -1]) / 2 : medianB[squareCells/2];

            processing->setPixel(x, y, qRgb(r, g, b));
        }
    }
}

void BlurMedian::cross(Image *original, Image *processing)
{
    int height = processing->height(), width = processing->width();
    uint squareSize = 3;
    int squareCells = squareSize*2-1;
    bool isEven = (squareCells % 2) == 0;
    QRgb tmpPx;
    int r, g, b, maskMeed = squareSize/2, i = 0, tx = 0, ty = 0;
    int medianR[squareCells], medianG[squareCells],  medianB[squareCells];

    for(int x = 0; x < width; x++)
    {
        tx = (x == 0) ? maskMeed : (x == width-1) ? -maskMeed : 0;
        for(int y = 0; y < height; y++)
        {
            i = 0;
            ty = (y == 0) ? maskMeed : (y == height-1) ? -maskMeed : 0;
            for(int r = 0; r < squareSize; r++)
            {
                tmpPx = original->pixel(x-(1-r)+tx, y);
                medianR[i] = qRed(tmpPx);
                medianG[i] = qGreen(tmpPx);
                medianB[i] = qBlue(tmpPx);
                i++;
            }

            for(int k = 0; k < squareSize; k++)
            {
                if(k == 1) continue;
                tmpPx = original->pixel(x, y-(1-k)+ty);
                medianR[i] = qRed(tmpPx);
                medianG[i] = qGreen(tmpPx);
                medianB[i] = qBlue(tmpPx);
                i++;
            }


            std::sort(medianR, medianR+squareCells);
            std::sort(medianG, medianG+squareCells);
            std::sort(medianB, medianB+squareCells);

            r = (isEven) ? (medianR[squareCells/2] + medianR[squareCells/2 -1]) / 2 : medianR[squareCells/2];
            g = (isEven) ? (medianG[squareCells/2] + medianG[squareCells/2 -1]) / 2 : medianG[squareCells/2];
            b = (isEven) ? (medianB[squareCells/2] + medianB[squareCells/2 -1]) / 2 : medianB[squareCells/2];

            processing->setPixel(x, y, qRgb(r, g, b));
        }
    }
}

void BlurMedian::adaptiveCross(Image *original, Image *processing)
{
    int height = processing->height(), width = processing->width();
    uint squareSize = 3;
    int squareCells = squareSize*2-1;
    bool isEven = (squareCells % 2) == 0;
    QRgb tmpPx;
    int r = 0, g = 0, b = 0, maskMeed = squareSize/2, i = 0, tx = 0, ty = 0;;
    int medianR[squareCells], medianG[squareCells],  medianB[squareCells];

    for(int x = 0; x < width; x++)
    {
        tx = (x == 0) ? maskMeed : (x == width-1) ? -maskMeed : 0;
        for(int y = 0; y < height; y++)
        {
            ty = (y == 0) ? maskMeed : (y == height-1) ? -maskMeed : 0;
            i=0;
            for(int r = 0; r < squareSize; r++)
            {
                tmpPx = original->pixel(x-(1-r)+tx, y);
                medianR[i] = qRed(tmpPx);
                medianG[i] = qGreen(tmpPx);
                medianB[i] = qBlue(tmpPx);
                i++;
            }

            for(int k = 0; k < squareSize; k++)
            {
                //To prevent duplicate center ceil (it's cross!)
                if(k == 1) continue;
                tmpPx = original->pixel(x, y-(1-k)+ty);
                medianR[i] = qRed(tmpPx);
                medianG[i] = qGreen(tmpPx);
                medianB[i] = qBlue(tmpPx);
                i++;
            }

            tmpPx = original->pixel(x, y);
            std::sort(medianR, medianR+squareCells);
            std::sort(medianG, medianG+squareCells);
            std::sort(medianB, medianB+squareCells);

            if(qRed(tmpPx) == medianR[0] || qRed(tmpPx) == medianR[squareCells-1])
                r = (isEven) ? (medianR[squareCells/2] + medianR[squareCells/2 -1]) / 2 : medianR[squareCells/2];
            else
                r = qRed(tmpPx);

            if(qGreen(tmpPx) == medianG[0] || qGreen(tmpPx) == medianG[squareCells-1])
                g = (isEven) ? (medianG[squareCells/2] + medianG[squareCells/2 -1]) / 2 : medianG[squareCells/2];
            else
                g = qGreen(tmpPx);

            if(qBlue(tmpPx) == medianB[0] || qBlue(tmpPx) == medianB[squareCells-1])
                b = (isEven) ? (medianB[squareCells/2] + medianB[squareCells/2 -1]) / 2 : medianB[squareCells/2];
            else
                b = qBlue(tmpPx);

            processing->setPixel(x, y, qRgb(r, g, b));
        }
    }
}

void BlurMedian::adaptiveSquare(Image *original, Image *processing, int squareSize)
{
    int height = processing->height(), width = processing->width();
    int squareCells = squareSize*squareSize;
    bool isEven = (squareCells % 2) == 0;
    QRgb tmpPx;
    int r, g, b, maskMeed = squareSize/2, i = 0, tx = 0, ty = 0;;
    int medianR[squareCells], medianG[squareCells],  medianB[squareCells];

    for(int x = 0; x < width; x++)
    {
        tx = (x == 0) ? maskMeed : (x == width-1) ? -maskMeed : 0;
        for(int y = 0; y < height; y++)
        {
            i = 0;
            ty = (y == 0) ? maskMeed : (y == height-1) ? -maskMeed : 0;
            for(int r = 0; r < squareSize; r++)
            {
                for(int k = 0; k < squareSize; k++)
                {
                    tmpPx = original->pixel(x-(maskMeed-k)+tx, y-(maskMeed-r)+ty);
                    medianR[i] = qRed(tmpPx);
                    medianG[i] = qGreen(tmpPx);
                    medianB[i] = qBlue(tmpPx);
                    i++;
                }
            }

            tmpPx = original->pixel(x, y);
            std::sort(medianR, medianR+squareCells);
            std::sort(medianG, medianG+squareCells);
            std::sort(medianB, medianB+squareCells);

            if(qRed(tmpPx) == medianR[0] || qRed(tmpPx) == medianR[squareCells-1])
                r = (isEven) ? (medianR[squareCells/2] + medianR[squareCells/2 -1]) / 2 : medianR[squareCells/2];
            else
                r = qRed(tmpPx);

            if(qGreen(tmpPx) == medianG[0] || qGreen(tmpPx) == medianG[squareCells-1])
                g = (isEven) ? (medianG[squareCells/2] + medianG[squareCells/2 -1]) / 2 : medianG[squareCells/2];
            else
                g = qGreen(tmpPx);

            if(qBlue(tmpPx) == medianB[0] || qBlue(tmpPx) == medianB[squareCells-1])
                b = (isEven) ? (medianB[squareCells/2] + medianB[squareCells/2 -1]) / 2 : medianB[squareCells/2];
            else
                b = qBlue(tmpPx);

            processing->setPixel(x, y, qRgb(r, g, b));
        }
    }
}
