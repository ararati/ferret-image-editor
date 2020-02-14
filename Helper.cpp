#include "Helper.h"

int Helper::sumColor(int color, int val)
{
    int sum = color + val;
    return valid_rgb(sum);
}

int Helper::valid_rgb(int color) {
    return (color < 0) ? 0 : (color > 255) ? 255 : color;
}
