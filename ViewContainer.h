#ifndef VIEWCONTAINER_H
#define VIEWCONTAINER_H

#include "image.h"

#include <qlabel.h>



class ViewContainer
{
public:
    ViewContainer();
    ViewContainer(QWidget* tab, QLabel* lb, Image* original, Image* process);
    QLabel* getViewLabel();
    Image* getOriginalImage();
    Image* getProcessImage();

    void setViewLabel(QLabel* lb);
    void setOriginalImage(Image* img);
    void setProcessImage(Image* img);
private:
    QWidget* tab;
    QLabel* outLabel;
    Image* originalImage;
    Image* processImage;
};

#endif // VIEWCONTAINER_H
