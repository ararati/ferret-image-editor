#include "SingleColorView.h"

void SingleColorView::process(Image *originalImg, Image *processImg, int colorIndex) {
    uint height = originalImg->height(), width = originalImg->width();

    float k;
    QRgb px;
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            px = originalImg->pixel(x, y);
            k = 0.2126 * qRed(px) + 0.7152 * qBlue(px) + 0.0722 * qGreen(px);

            QColor color(0, 0, 0);
            if(colorIndex == 0)
                color.setRed(k);
            else if(colorIndex == 1)
                color.setGreen(k);
            else
                color.setBlue(k);

            processImg->setPixel(x, y, color.rgb());

        }
    }
}
