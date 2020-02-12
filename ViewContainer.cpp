#include "ViewContainer.h"

ViewContainer::ViewContainer()
{

}

ViewContainer::ViewContainer(QWidget *tab, QLabel *lb, Image *original, Image *process)
{
    this->tab = tab;
    this->outLabel = lb;
    this->originalImage = original;
    this->processImage = process;
}

QLabel *ViewContainer::getViewLabel()
{
    return outLabel;
}

Image *ViewContainer::getOriginalImage()
{
    return originalImage;
}

Image *ViewContainer::getProcessImage()
{
    return processImage;
}

void ViewContainer::setViewLabel(QLabel *lb)
{
    this->outLabel = lb;
}

void ViewContainer::setOriginalImage(Image *img)
{
    this->originalImage = img;
}

void ViewContainer::setProcessImage(Image *img)
{
    this->processImage = img;
}
