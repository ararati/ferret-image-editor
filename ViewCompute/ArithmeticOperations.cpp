#include "ArithmeticOperations.h"

void ArithmeticOperations::min(Image* original, Image *processing, Image *image2)
{
    int height = std::min(processing->height(), image2->height());
    int width = std::min(processing->width(), image2->width());
    for(int x = 0; x < width; x++)
        for(int y = 0; y < height; y++)
        {
            QRgb p1 = original->pixel(x, y);
            QRgb p2 = image2->pixel(x, y);
            processing->setPixel(x, y, qRgb(
                                     std::min(qRed(p1), qRed(p2)),
                                     std::min(qGreen(p1), qGreen(p2)),
                                     std::min(qBlue(p1), qBlue(p2))));
        }
}

void ArithmeticOperations::max(Image* original, Image *processing, Image *image2)
{
    int height = std::min(processing->height(), image2->height());
    int width = std::min(processing->width(), image2->width());
    for(int x = 0; x < width; x++)
        for(int y = 0; y < height; y++)
        {
            QRgb p1 = original->pixel(x, y);
            QRgb p2 = image2->pixel(x, y);
            processing->setPixel(x, y, qRgb(
                                     std::max(qRed(p1), qRed(p2)),
                                     std::max(qGreen(p1), qGreen(p2)),
                                     std::max(qBlue(p1), qBlue(p2))));
        }
}

void ArithmeticOperations::average(Image* original, Image *processing, Image *image2)
{
    int height = std::min(processing->height(), image2->height());
    int width = std::min(processing->width(), image2->width());
    for(int x = 0; x < width; x++)
        for(int y = 0; y < height; y++)
        {
            QRgb p1 = original->pixel(x, y);
            QRgb p2 = image2->pixel(x, y);
            processing->setPixel(x, y, qRgb(
                                     (qRed(p1)+qRed(p2)) /2,
                                     (qGreen(p1)+qGreen(p2))/2,
                                     (qBlue(p1)+qBlue(p2))/2));
        }
}

void ArithmeticOperations::sum(Image* original, Image *processing, Image *image2)
{
    int height = std::min(processing->height(), image2->height());
    int width = std::min(processing->width(), image2->width());
    for(int x = 0; x < width; x++)
        for(int y = 0; y < height; y++)
        {
            QRgb p1 = original->pixel(x, y);
            QRgb p2 = image2->pixel(x, y);
            processing->setPixel(x, y, qRgb(
                                     std::min((qRed(p1)+qRed(p2)), 255),
                                     std::min((qGreen(p1)+qGreen(p2)), 255),
                                     std::min((qBlue(p1)+qBlue(p2)), 255)));
        }
}

void ArithmeticOperations::diff(Image* original, Image *processing, Image *image2)
{
    int height = std::min(processing->height(), image2->height());
    int width = std::min(processing->width(), image2->width());
    for(int x = 0; x < width; x++)
        for(int y = 0; y < height; y++)
        {
            QRgb p1 = original->pixel(x, y);
            QRgb p2 = image2->pixel(x, y);
            processing->setPixel(x, y, qRgb(
                                     std::max(qRed(p1)-qRed(p2), 0),
                                     std::max(qGreen(p1)-qGreen(p2), 0),
                                     std::max(qBlue(p1)-qBlue(p2), 0)));
        }
}

void ArithmeticOperations::mul(Image* original, Image *processing, Image *image2)
{
    int height = std::min(processing->height(), image2->height());
    int width = std::min(processing->width(), image2->width());
    for(int x = 0; x < width; x++)
        for(int y = 0; y < height; y++)
        {
            QRgb p1 = original->pixel(x, y);
            QRgb p2 = image2->pixel(x, y);
            processing->setPixel(x, y, qRgb(
                                     255*(qRed(p1)  /255.0 * (qRed(p2)/255.0)),
                                     255*(qGreen(p1)/255.0 * (qGreen(p2)/255.0)),
                                     255*(qBlue(p1) /255.0 * (qBlue(p2)/255.0)))
                                 );
        }
}

void ArithmeticOperations::OR(Image *original, Image *processing, Image *image2)
{
    int height = std::min(processing->height(), image2->height());
    int width = std::min(processing->width(), image2->width());
    for(int x = 0; x < width; x++)
        for(int y = 0; y < height; y++)
        {
            QRgb p1 = original->pixel(x, y);
            QRgb p2 = image2->pixel(x, y);
            processing->setPixel(x, y, qRgb(
                                     qRed(p1) | qRed(p2),
                                     qGreen(p1) | qGreen(p2),
                                     qBlue(p1) | qBlue(p2))
                                 );
        }
}

void ArithmeticOperations::AND(Image *original, Image *processing, Image *image2)
{
    int height = std::min(processing->height(), image2->height());
    int width = std::min(processing->width(), image2->width());
    for(int x = 0; x < width; x++)
        for(int y = 0; y < height; y++)
        {
            QRgb p1 = original->pixel(x, y);
            QRgb p2 = image2->pixel(x, y);
            processing->setPixel(x, y, qRgb(
                                     qRed(p1) & qRed(p2),
                                     qGreen(p1) & qGreen(p2),
                                     qBlue(p1) & qBlue(p2))
                                 );
        }
}

void ArithmeticOperations::XOR(Image *original, Image *processing, Image *image2)
{
    int height = std::min(processing->height(), image2->height());
    int width = std::min(processing->width(), image2->width());
    for(int x = 0; x < width; x++)
        for(int y = 0; y < height; y++)
        {
            QRgb p1 = original->pixel(x, y);
            QRgb p2 = image2->pixel(x, y);
            processing->setPixel(x, y, qRgb(
                                     qRed(p1) ^ qRed(p2),
                                     qGreen(p1) ^ qGreen(p2),
                                     qBlue(p1) ^ qBlue(p2))
                                 );
        }
}

void ArithmeticOperations::dilate(Image *original, Image *processing)
{
    uint height = processing->height(), width = processing->width(), r, g, b;
    for(int x = 2; x < width-2; x++)
    {
        for(int y = 2; y < height-2; y++)
        {
            for(int i = 0; i < 5; i++) {
                for(int j = 0; j < 5; j++) {
                    QRgb px = original->pixel(x-(2-i), y-(2-j));
                    if(qRed(px) == 0) {
                        processing->setPixel(x, y, qRgb(0, 0, 0));
                        break;
                    }
                }
            }
        }
    }
}

void ArithmeticOperations::erosion(Image *original, Image *processing)
{
    uint height = processing->height(), width = processing->width(), r, g, b;
    for(int x = 2; x < width-2; x++)
    {
        for(int y = 2; y < height-2; y++)
        {
            for(int i = 0; i < 5; i++) {
                for(int j = 0; j < 5; j++) {
                    QRgb px = original->pixel(x-(2-i), y-(2-j));
                    if(qRed(px) > 0) {
                        processing->setPixel(x, y, qRgb(255, 255, 255));
                        break;
                    }
                }
            }
        }
    }
}
