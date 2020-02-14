#include "BrightnessView.h"

#include <Helper.h>

void BrightnessView::process(Image* original, Image* processed, int brightness)
{
    uint height = original->height(), width = original->width();
    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            QRgb px = original->pixel(x, y);
            processed->setPixel(x, y, qRgb(
                                        Helper::sumColor(qRed(px), brightness),
                                        Helper::sumColor(qGreen(px), brightness),
                                        Helper::sumColor(qBlue(px), brightness)
                                    )
                                );
        }
    }
}
