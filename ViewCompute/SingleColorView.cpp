#include "SingleColorView.h"

void SingleColorView::process(Image *originalImg, Image *processImg, int colorIndex) {
    uint height = originalImg->getHeight(), width = originalImg->getWidth();
    for(int row = 0; row < height; row++)
    {
        for(int col = 0; col < width; col++)
        {
            Vec3b px = originalImg->getCvImg().at<Vec3b>(row, col);
            for(int i = 0; i < 3; i++) {
                if(i == colorIndex) {
                    processImg->getCvImg().at<Vec3b>(row, col)[i] = 0.2126 * px[2] + 0.7152 * px[0] + 0.0722 * px[1];
                } else {
                    processImg->getCvImg().at<Vec3b>(row, col)[i] = 0;
                }
            }
        }
    }
}
