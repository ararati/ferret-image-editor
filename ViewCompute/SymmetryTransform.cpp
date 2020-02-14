#include "SymmetryTransform.h"
#include <QDebug>

void SymmetryTransform::transformHorizontal(Image *originalImg, Image *processImg)
{
    uint height = processImg->height(), width = processImg->width();
    for(int row = 0; row < height; row++)
    {
        for(int col = 0; col < width/2; col++)
        {
//            processImg->getCvImg().at<Vec3b>(row, col) =  processImg->getCvImg().at<Vec3b>(row, width-col);
        }
    }
}

void SymmetryTransform::transformVertical(Image *originalImg, Image *processImg)
{
    try {
    uint height = processImg->height()-1, width = processImg->width();
    for(int row = 0; row < height/2; row++)
    {
        for(int col = 0; col < width; col++)
        {
            //qInfo() << height-row;
//            processImg->getCvImg().at<Vec3b>(row, col) =  processImg->getCvImg().at<Vec3b>(height-row, col);
        }
    }
    } catch(Exception &e) {
        qInfo() << e.what();
    }
}
