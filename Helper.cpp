#include "Helper.h"

int Helper::sumColor(int color, int val)
{
    int sum = color + val;
    return (sum < 0) ? 0 : (sum > 255) ? 255 : sum;
}
