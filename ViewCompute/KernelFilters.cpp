#include "KernelFilters.h"
#include <QtDebug>

KernelFilters::KernelFilters()
{

}

void KernelFilters::zeros(double (&arr)[3][3])
{
    double m[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    fill(m, arr);
}

void KernelFilters::leftSobel(double (&arr)[3][3])
{
    double m[3][3] = {
        {1, 0, -1},
        {2, 0, -2},
        {1, 0, -1}
    };

    fill(m, arr);
}

void KernelFilters::bottomSobel(double (&arr)[3][3])
{
    double m[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    fill(m, arr);
}

void KernelFilters::topSobel(double (&arr)[3][3])
{
    double m[3][3] = {
        {1, 2, 1},
        {0, 0, 0},
        {-1, -2, -1}
    };

    fill(m, arr);
}

void KernelFilters::rightSobel(double (&arr)[3][3])
{
    double m[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    fill(m, arr);
}

void KernelFilters::sharpen(double (&arr)[3][3])
{
    double m[3][3] = {
        {-1, -1, -1},
        {-1, 8, -1},
        {-1, -1, -1}
    };

    fill(m, arr);
}

void KernelFilters::smooth(double (&arr)[3][3])
{
    double m[3][3] = {
        {0.1, 0.1, 0.1},
        {0.1, 0.1, 0.1},
        {0.1, 0.1, 0.1}
    };

    fill(m, arr);
}

void KernelFilters::horizontalLines(double (&arr)[3][3])
{
    double m[3][3] = {
        {-1, -1, -1},
        {2, 2, 2},
        {-1, -1, -1}
    };

    fill(m, arr);
}

void KernelFilters::fill(double (&from)[3][3], double (&to)[3][3]) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            to[i][j] = from[i][j];
        }
    }
}
