#include "SymmetryTransform.h"

void SymmetryTransform::transformHorizontal(Image *originalImg, Image *processImg)
{
    uint height = processImg->getHeight(), width = processImg->getWidth();
    for(int row = 0; row < height; row++)
    {
        for(int col = 0; col < width/2; col++)
        {
            processImg->getCvImg().at<Vec3b>(row, col) =  processImg->getCvImg().at<Vec3b>(row, width-col);
        }
    }
}

void SymmetryTransform::transformVertical(Image *originalImg, Image *processImg)
{
    uint height = processImg->getHeight(), width = processImg->getWidth();
    for(int row = 0; row < height/2; row++)
    {
        for(int col = 0; col < width; col++)
        {
            processImg->getCvImg().at<Vec3b>(row, col) =  processImg->getCvImg().at<Vec3b>(height-row, col);
        }
    }
}
