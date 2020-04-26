#include "Image.h"
#include "Image.h"

#include <QFile>

Image::Image()
{

}

Image::Image(QString path) : QImage(path)
{
    this->path_ = path;
}

bool Image::sameSize(QImage *img) {
    return (this->width() == img->width() && this->height() == img->height());
}

void Image::copyFrom(QImage *img)
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
}

void Image::setPath(QString path)
{
    this->path_ = path;
}
