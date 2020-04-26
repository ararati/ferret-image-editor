QT       += core gui opengl printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

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
    Widgets/ArithmeticWidget.cpp \
    Widgets/EffectsWidget.cpp \
    Widgets/KernelWidget.cpp \
    Image.cpp \
    ViewCompute/ArithmeticOperations.cpp \
    ViewCompute/BinaryView.cpp \
    ViewCompute/Blur/BlurAverage.cpp \
    ViewCompute/Blur/BlurGaus.cpp \
    ViewCompute/Blur/BlurMedian.cpp \
    ViewCompute/BrightnessView.cpp \
    ViewCompute/ContrastView.cpp \
    ViewCompute/Filter.cpp \
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
    Widgets/UndoRedoActionsWidget.cpp \
    Widgets/ZoomWidget.cpp \
    Windows/PlotDialog.cpp \
    main.cpp \
    mainwindow.cpp \
    Widgets/qcustomplot.cpp

HEADERS += \
    Image.h \
    Widgets/ArithmeticWidget.h \
    Widgets/EffectsWidget.h \
    Widgets/KernelWidget.h \
    ViewCompute/ArithmeticOperations.h \
    ViewCompute/BinaryView.h \
    ViewCompute/Blur/BlurAverage.h \
    ViewCompute/Blur/BlurGaus.h \
    ViewCompute/Blur/BlurMedian.h \
    ViewCompute/BrightnessView.h \
    ViewCompute/ContrastView.h \
    ViewCompute/Filter.h \
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
    Widgets/UndoRedoActionsWidget.h \
    Widgets/ZoomWidget.h \
    Windows/PlotDialog.h \
    mainwindow.h \
    Widgets/qcustomplot.h

FORMS += \
    Widgets/arithmeticwidget.ui \
    Widgets/effectswidget.ui \
    Widgets/kernelwidget.ui \
    Widgets/undoRedoActionsWidget.ui \
    Widgets/zoomwidget.ui \
    Windows/PlotDialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    EditorResources.qrc
