#include "Noise.h"
#include <QtDebug>
#include <random>

default_random_engine rngX;
default_random_engine rngY;
//default_random_engine colorBW;

void Noise::proccess(Image *original, Image *processing, unsigned int countWhite, unsigned int countBlack)
{
    int height = processing->height()-1, width = processing->width()-1;

    int rX, rY;
    for(int i = 0; i < countWhite; i++)
    {
            uniform_int_distribution<int> randX(0, width);
            uniform_int_distribution<int> randY(0, height);

            rX = randX(rngX);
            rY = randY(rngX);

            processing->setPixel(rX, rY, qRgb(255, 255, 255));
    }

    for(int i = 0; i < countBlack; i++)
    {
            uniform_int_distribution<int> randX(0, width);
            uniform_int_distribution<int> randY(0, height);

            rX = randX(rngX);
            rY = randY(rngX);

            processing->setPixel(rX, rY, qRgb(0, 0, 0));
    }
}

void Noise::bipolar(Image *original, Image *processing, unsigned int count)
{
    int height = processing->height()-1, width = processing->width()-1;

    int rX, rY;
    for(int i = 0; i < count; i++)
    {
            uniform_int_distribution<int> randX(1, width-1);
            uniform_int_distribution<int> randY(1, height-1);

            rX = randX(rngX);
            rY = randY(rngX);

            processing->setPixel(rX, rY, qRgb(255, 255, 255));
            processing->setPixel(rX+1, rY+1, qRgb(0, 0, 0));
            processing->setPixel(rX-1, rY-1, qRgb(0, 0, 0));
    }
}
