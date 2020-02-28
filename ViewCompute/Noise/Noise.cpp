#include "Noise.h"
#include <QtDebug>
#include <random>

default_random_engine rngX;
default_random_engine rngY;
//default_random_engine colorBW;

void Noise::proccess(Image *original, Image *processing, unsigned int countWhite, unsigned int countBlack)
{
    int height = processing->height(), width = processing->width();

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
