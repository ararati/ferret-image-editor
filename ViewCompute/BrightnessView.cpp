#include "BrightnessView.h"

void BrightnessView::process(Image* original, Image* processed, int brightness)
{
    uint height = original->height(), width = original->width();
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            QRgb px = original->pixel(x, y);
            processed->setPixel(x, y, qRgb(
                                        Filter::sumColor(qRed(px), brightness),
                                        Filter::sumColor(qGreen(px), brightness),
                                        Filter::sumColor(qBlue(px), brightness)
                                    )
                                );
        }
    }
}
