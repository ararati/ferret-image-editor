#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <iostream>

using namespace std;

class Image : public QImage
{
    private:
        QString path_;

        QImage fromFile(QString path, int code);

    public:
        const QString & path() const { return path_;}

        Image();
        Image(QString path);

        void copyFrom(QImage *);
        void setPath(QString path);
        bool sameSize(QImage *img);
};

#endif // IMAGE_H
