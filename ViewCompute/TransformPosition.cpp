#include "TransformPosition.h"

void TransformPosition::transformX(Image *original, Image *processImg, int step)
{
    uint height = original->getHeight(), width = original->getWidth();
    for(int row = 0; row < height; row++)
    {
        for(int col = 0; col < width; col++)
        {
            if(col+step < processImg->getWidth()) {
                processImg->getCvImg().at<Vec3b>(row,col) = processImg->getCvImg().at<Vec3b>(row,col+step);
            } else {
                processImg->getCvImg().at<Vec3b>(row,col) = Vec3b(255, 255, 255);
            }
        }
    }
}
