#ifndef ARITHMETICOPERATIONS_H
#define ARITHMETICOPERATIONS_H

#include <image.h>
#include <algorithm>

class ArithmeticOperations
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

};

#endif // ARITHMETICOPERATIONS_H
