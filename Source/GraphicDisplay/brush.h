#ifndef TOOLBRUSH_H
#define TOOLBRUSH_H

#include <QtWidgets>
#include "pencil.h"

class ToolBrush : public ToolPencil
{
    Q_OBJECT

protected:
    virtual void paintEvent(QPaintEvent *event);
public:
    ToolBrush(QImage *display, QColor *selectedColor1, QColor *selectedColor2, QToolBar *uptool, QStatusBar *statusInfo, int *penWidthPtr, QWidget *parent = nullptr);
};

#endif // TOOLBRUSH_H
