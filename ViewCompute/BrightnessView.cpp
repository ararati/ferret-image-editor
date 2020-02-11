#include "BrightnessView.h"

#include <Helper.h>

void BrightnessView::process(Image* originalImg, Image* processImg, int brightness)
{
    uint height = originalImg->getHeight(), width = originalImg->getWidth();
    for(int row = 0; row < height; row++)
    {
        for(int col = 0; col < width; col++)
        {
            Vec3b px = originalImg->getCvImg().at<Vec3b>(row, col);

            processImg->getCvImg().at<Vec3b>(row, col) = Vec3b(
                        Helper::sumColor(px[0], brightness),
                        Helper::sumColor(px[1], brightness),
                        Helper::sumColor(px[2], brightness)
                    );
        }
    }
}
