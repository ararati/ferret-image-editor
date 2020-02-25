#include "BinaryView.h"
#include "GrayscaleView.h"

void BinaryView::process(Image *original, Image *processed, int treshold)
{
//    GrayscaleView::process(originalImg, processImg);

    uint height = processed->height(), width = processed->width();
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            QRgb px = original->pixel(x, y);
            int bin = (qBlue(px) >= treshold) ? 255 : 0;
            processed->setPixel(x, y, qRgb(bin, bin, bin));
//            int color = (originalImg->getCvImg().at<Vec3b>(row, col)[0] >= treshold) ? 255 : 0;
//            for(int i = 0; i < 3; i++) {
//                    processImg->getCvImg().at<Vec3b>(row, col)[i] = color;
//            }
        }
    }
}
