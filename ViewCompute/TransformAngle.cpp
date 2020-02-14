#include "TransformAngle.h"

void TransformAngle::rotateLeft(Image *original, Image *image)
{
    uint height = original->height(), width = original->width();

//    Mat rotatedImg(original->getCvImg().cols, original->getCvImg().rows, CV_8UC3, Scalar(255, 255, 255));
    //Mat rotatedImg(3000, 3000, CV_8UC3, Scalar(255, 255, 255));

    int x0 = 1000;
    int y0 = 1000;
    float angle = 90;
    for(int row = 0; row < height; row++)
        for(int col = 0; col < width; col++)
        {
            //float x = cos(angle) * (col-x0) - sin(angle) * (row - y0) + x0;
            //float y = sin(angle) * (col-x0) + cos(angle) * (row - y0) + y0;
            //rotatedImg.at<Vec3b>(x, y) = original->getCvImg().at<Vec3b>(row, col);
//            rotatedImg.at<Vec3b>(col, row) = original->getCvImg().at<Vec3b>(row, col);

        }

    //image->setSvImg(rotatedImg);
}

void TransformAngle::rotateRight(Image *original, Image *processImg)
{

}
