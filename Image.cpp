#include "image.h"
#include "image.h"

#include <QFile>

Image::Image()
{

}

Image::Image(QString path) : QImage(path)
{
    this->path_ = path;
}

QImage Image::toQImage()
{
//    this->cv_img.copyTo(this->tmp_img);
    //imshow("f", this->tmp_img);
//    cvtColor(this->tmp_img, this->tmp_img, COLOR_RGB2BGR);
//    QImage image = QImage((uchar*) this->tmp_img.data, this->tmp_img.cols, this->tmp_img.rows, this->tmp_img.step, QImage::Format_RGB888);

    //cvtColor(this->cv_img, this->cv_img, COLOR_BGR2RGB);

    //    return image;
}

bool Image::sameSize(QImage *img) {
    return (this->width() == img->width() && this->height() == img->height());
}

void Image::copyFrom(Image *img)
{
    if(!sameSize(img)) {
        this->scaled(img->width(), img->height());
    }

    for(int x = 0; x < img->width(); x++)
        for(int y = 0; y < img->height(); y++) {
            this->setPixel(x, y, img->pixel(x, y));
        }
}


QImage Image::fromFile(QString path, int code)
{
    this->path_ = path;

    return QImage(this->path_);

//    QFile file(QString::fromStdString(path));
//    Mat m;
//    if(file.open(QIODevice::ReadOnly))
//    {
//        qint64 sz = file.size();
//        std::vector<uchar> buf(sz);
//        file.read((char*)buf.data(), sz);
//        m = imdecode(buf, code);
//    }

//     return m;
    //return imread(path, code);
}

//Mat Image::colorTable()
//{
//    return this->original;
//}

//string Image::getPath()
//{
//    return this->imageSourcePath;
//}

void Image::setPath(QString path)
{
    this->path_ = path;
}

//void Image::setSvImg(Mat newImg) {
//    this->cv_img.release();

//    this->cv_img = newImg;

//    this->width = this->cv_img.cols;
//    this->height = this->cv_img.rows;
//}
