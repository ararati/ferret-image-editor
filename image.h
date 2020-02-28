#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <iostream>

//#include <opencv2/opencv.hpp>

using namespace std;
//using namespace cv;

class Image : public QImage
{
    private:
        QString path_;

        QImage fromFile(QString path, int code);

    public:
        const QString & path() const { return path_;}

        Image();
        Image(QString path);

        QImage toQImage();
        void copyFrom(QImage *);
        void setPath(QString path);
        bool sameSize(QImage *img);

        QList<int> at(int x, int y);
};

#endif // IMAGE_H
