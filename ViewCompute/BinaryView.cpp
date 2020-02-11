#include "BinaryView.h"
#include "GrayscaleView.h"

void BinaryView::process(Image *originalImg, Image *processImg, int treshold)
{
//    GrayscaleView::process(originalImg, processImg);

    uint height = originalImg->getHeight(), width = originalImg->getWidth();
    for(int row = 0; row < height; row++)
    {
        for(int col = 0; col < width; col++)
        {
            int color = (originalImg->getCvImg().at<Vec3b>(row, col)[0] >= treshold) ? 255 : 0;
            for(int i = 0; i < 3; i++) {
                    processImg->getCvImg().at<Vec3b>(row, col)[i] = color;
            }
        }
    }
}
