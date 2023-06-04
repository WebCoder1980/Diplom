#ifndef TOOLRULLER_H
#define TOOLRULLER_H

#include <QtWidgets>
#include "toolcore.h"

class ToolRuller : public ToolCore
{
    Q_OBJECT
    int pointBeginX, pointBeginY, pointEndX, pointEndY;
    bool isPressed;
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
public:
    void isSelect();
    ToolRuller(QImage *display, QToolBar *uptool, QStatusBar *statusInfo, QWidget *parent = nullptr);
};

#endif // TOOLRULLER_H
