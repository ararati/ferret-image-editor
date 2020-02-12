#include "TransformPosition.h"
#include <QtDebug>

void TransformPosition::transformX(Image *original, Image *processImg, int step)
{
    uint height = original->getHeight(), width = original->getWidth();

    int startCol = (step > 0) ? width : 0;
    step *= -1;

    for(int row = 0; row < height; row++)
    {
        for(int col = 0; col < width; col++)
        {
            //With repeat image
            //processImg->getCvImg().at<Vec3b>(row, col) = original->getCvImg().at<Vec3b>(row, startCol+col+step);
            if(col + step < width)
                processImg->getCvImg().at<Vec3b>(row, col) = original->getCvImg().at<Vec3b>(row, startCol+col+step);
            else
                processImg->getCvImg().at<Vec3b>(row, col) = Vec3b(255, 255, 255);

        }
    }
}


void TransformPosition::transformY(Image *original, Image *processImg, int step)
{
    uint height = original->getHeight(), width = original->getWidth();

    int startRow = (step > 0) ? height : 0;
    //step *= -1;


    for(int row = 0; row < height; row++)
    {
        for(int col = 0; col < width; col++)
        {
            if(row + step < height)
                processImg->getCvImg().at<Vec3b>(row, col) = original->getCvImg().at<Vec3b>(row+step, col);
            else
                processImg->getCvImg().at<Vec3b>(row, col) = Vec3b(255, 255, 255);
        }
    }
}
