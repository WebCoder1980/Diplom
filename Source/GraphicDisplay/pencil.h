#ifndef TOOLPENCIL_H
#define TOOLPENCIL_H

#include <QtWidgets>
#include "toolcore.h"

class ToolPencil : public ToolCore
{
    protected:
    int pointBeginX, pointBeginY, pointEndX, pointEndY;
    int *penWidthPtr;
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
public:
    ToolPencil(QImage *display, QColor *selectedColor1, QColor *selectedColor2, QToolBar *uptool, QStatusBar *statusInfo, int *penWidth, QWidget *parent = nullptr);
public slots:
};

#endif // TOOLPENCIL_H
