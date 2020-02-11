#ifndef SYMMETRYTRANSFORM_H
#define SYMMETRYTRANSFORM_H

#include <image.h>



class SymmetryTransform
{
public:
    static void transformHorizontal(Image* originalImg, Image* processImg);
    static void transformVertical(Image *originalImg, Image *processImg);
};

#endif // SYMMETRYTRANSFORM_H
