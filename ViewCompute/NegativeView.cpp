#include "NegativeView.h"

void NegativeView::process(Image* originalImg, Image* processImg)
{
    uint height = originalImg->getHeight(), width = originalImg->getWidth();
    for(int row = 0; row < height; row++)
    {
        for(int col = 0; col < width; col++)
        {
            Vec3b px = originalImg->getCvImg().at<Vec3b>(row, col);

            processImg->getCvImg().at<Vec3b>(row, col) = Vec3b(
                        255-px[0],
                        255-px[1],
                        255-px[2]
                    );
        }
    }
}
