#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <iostream>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Image
{
    private:
        Mat cv_img;
        Mat tmp_img;
        string imageSourcePath;
        uint width;
        uint height;
        Mat fromFile(string path, int code);

    public:
        Image();
        Image(string path, int code = IMREAD_UNCHANGED);
        QImage toQImage();
        Mat getCvImg();
        uint getWidth();
        uint getHeight();
};

#endif // IMAGE_H
