#include "Filter.h"

int Filter::sumColor(int color, int val)
{
    int sum = color + val;

    return getValidRgb(sum);
}

int Filter::getValidRgb(int color) {
    return (color < 0) ? 0 : (color > 255) ? 255 : color;
}
