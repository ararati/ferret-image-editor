QT       += core gui opengl printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

#INCLUDEPATH += D:\OpenCV\opencv-mingw\install\include

#LIBS += D:\OpenCV\opencv-mingw\bin\libopencv_core420.dll
#LIBS += D:\OpenCV\opencv-mingw\bin\libopencv_highgui420.dll
#LIBS += D:\OpenCV\opencv-mingw\bin\libopencv_imgcodecs420.dll
#LIBS += D:\OpenCV\opencv-mingw\bin\libopencv_imgproc420.dll
#LIBS += D:\OpenCV\opencv-mingw\bin\libopencv_calib3d420.dll

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Helper.cpp \
    Image.cpp \
    ViewCompute/BinaryView.cpp \
    ViewCompute/Blur/BlurAverage.cpp \
    ViewCompute/Blur/BlurGaus.cpp \
    ViewCompute/BrightnessView.cpp \
    ViewCompute/ContrastView.cpp \
    ViewCompute/GrayscaleView.cpp \
    ViewCompute/HistogramEqualization.cpp \
    ViewCompute/KernelFilters.cpp \
    ViewCompute/MaskFilter.cpp \
    ViewCompute/NegativeView.cpp \
    ViewCompute/Noise/Noise.cpp \
    ViewCompute/SingleColorView.cpp \
    ViewCompute/SymmetryTransform.cpp \
    ViewCompute/TransformAngle.cpp \
    ViewCompute/TransformPosition.cpp \
    ViewContainer.cpp \
    Windows/CoverImageDialog.cpp \
    Windows/PlotDialog.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    Helper.h \
    ViewCompute/BinaryView.h \
    ViewCompute/Blur/BlurAverage.h \
    ViewCompute/Blur/BlurGaus.h \
    ViewCompute/BrightnessView.h \
    ViewCompute/ContrastView.h \
    ViewCompute/GrayscaleView.h \
    ViewCompute/HistogramEqualization.h \
    ViewCompute/KernelFilters.h \
    ViewCompute/MaskFilter.h \
    ViewCompute/NegativeView.h \
    ViewCompute/Noise/Noise.h \
    ViewCompute/SingleColorView.h \
    ViewCompute/SymmetryTransform.h \
    ViewCompute/TransformAngle.h \
    ViewCompute/TransformPosition.h \
    ViewContainer.h \
    Windows/CoverImageDialog.h \
    Windows/PlotDialog.h \
    image.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    Windows/CoverImageDialog.ui \
    Windows/PlotDialog.ui \
    Windows/PlotWindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    EditorResources.qrc
