#ifndef TOOLERASSER_H
#define TOOLERASSER_H

#include <QtWidgets>
#include "toolcore.h"

class ToolErasser : public ToolCore
{
    Q_OBJECT
    int pointBeginX, pointBeginY, pointEndX, pointEndY;
    int *penWidthPtr;
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    void uptool_selectColor1();
    void uptool_selectColor2();
public:
    void isSelect();
    ToolErasser(QImage *display, QToolBar *uptool, QStatusBar *statusInfo, int *penWidth, QWidget *parent = nullptr);
};

#endif // TOOLERASSER_H
