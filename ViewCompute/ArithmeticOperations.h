#ifndef ARITHMETICOPERATIONS_H
#define ARITHMETICOPERATIONS_H

#include "Filter.h"
#include <Image.h>
#include <algorithm>

class ArithmeticOperations  : protected Filter
{
public:
    static void min(Image* original, Image* processing, Image* image);
    static void max(Image* original, Image* processing, Image* image);
    static void average(Image* original, Image* processing, Image* image);
    static void sum(Image* original, Image* processing, Image* image);
    static void diff(Image* original, Image* processing, Image* image);
    static void mul(Image* original, Image* processing, Image* image);
    static void OR(Image* original, Image* processing, Image* image);
    static void AND(Image* original, Image* processing, Image* image);
    static void XOR(Image* original, Image* processing, Image* image);
    static void dilate(Image* original, Image* processing);
    static void erosion(Image* original, Image* processing);

};

#endif // ARITHMETICOPERATIONS_H
