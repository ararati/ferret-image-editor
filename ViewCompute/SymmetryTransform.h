#ifndef SYMMETRYTRANSFORM_H
#define SYMMETRYTRANSFORM_H

#include "Filter.h"

#include <Image.h>

class SymmetryTransform  : protected Filter
{
public:
    static void transformHorizontal(Image* originalImg, Image* processImg);
    static void transformVertical(Image *originalImg, Image *processImg);
};

#endif // SYMMETRYTRANSFORM_H
