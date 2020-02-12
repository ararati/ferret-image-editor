#include "image.h"

#include <QFile>

Image::Image()
{

}

Image::Image(string path, int code)
{
    this->cv_img = this->fromFile(path, code);

    this->imageSourcePath = path;
    this->width = this->cv_img.cols;
    this->height = this->cv_img.rows;
}

QImage Image::toQImage()
{
    this->cv_img.copyTo(this->tmp_img);
    //imshow("f", this->tmp_img);
    cvtColor(this->tmp_img, this->tmp_img, COLOR_RGB2BGR);
    QImage image = QImage((uchar*) this->tmp_img.data, this->tmp_img.cols, this->tmp_img.rows, this->tmp_img.step, QImage::Format_RGB888);

    //cvtColor(this->cv_img, this->cv_img, COLOR_BGR2RGB);

    return image;
}


Mat Image::fromFile(string path, int code)
{
    QFile file(QString::fromStdString(path));
    Mat m;
    if(file.open(QIODevice::ReadOnly))
    {
        qint64 sz = file.size();
        std::vector<uchar> buf(sz);
        file.read((char*)buf.data(), sz);
        m = imdecode(buf, code);
    }

     return m;
    //return imread(path, code);
}

Mat Image::getCvImg()
{
    return this->cv_img;
}

uint Image::getWidth()
{
    return this->width;
}

uint Image::getHeight()
{
    return this->height;
}

string Image::getPath()
{
    return this->imageSourcePath;
}

void Image::setPath(string val)
{
    this->imageSourcePath = val;
}

void Image::setSvImg(Mat newImg) {
    this->cv_img.release();

    this->cv_img = newImg;

    this->width = this->cv_img.cols;
    this->height = this->cv_img.rows;
}
