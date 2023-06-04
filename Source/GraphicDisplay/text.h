#ifndef TOOLTEXT_H
#define TOOLTEXT_H

#include <QtWidgets>
#include "toolcore.h"

class ToolText : public ToolCore
{
    Q_OBJECT
    int pointBeginX, pointBeginY, pointEndX, pointEndY;
    bool paintText;
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
public:
    ToolText(QImage *display, QColor *selectedColor1, QColor *selectedColor2, QToolBar *uptool, QStatusBar *statusInfo, int *penWidth, QWidget *parent = nullptr);
};

#endif // TOOLTEXT_H
