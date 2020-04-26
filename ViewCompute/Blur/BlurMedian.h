#ifndef BLURMEDIAN_H
#define BLURMEDIAN_H

#include <Image.h>
#include <ViewCompute/Filter.h>

class BlurMedian : protected Filter
{
public:
    static void square(Image *original, Image *processed);
    static void adaptiveSquare(Image *original, Image *processed, int squareSize = 3);
    static void cross(Image *original, Image *processing);
    static void adaptiveCross(Image *original, Image *processing);
};

#endif // BLURMEDIAN_H
