#ifndef KERNELFILTERS_H
#define KERNELFILTERS_H


class KernelFilters
{
public:
    KernelFilters();
    static void leftSobel(double (&arr)[3][3]);
    static void bottomSobel(double (&arr)[3][3]);
    static void topSobel(double (&arr)[3][3]);
    static void rightSobel(double (&arr)[3][3]);
    static void sharpen(double (&arr)[3][3]);
    static void fill(double (&from)[3][3], double (&to)[3][3]);
    static void zeros(double (&arr)[3][3]);
    static void smooth(double (&arr)[3][3]);
    static void horizontalLines(double (&arr)[3][3]);
};

#endif // KERNELFILTERS_H
