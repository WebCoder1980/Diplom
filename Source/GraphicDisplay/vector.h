#ifndef TOOLVECTOR_H
#define TOOLVECTOR_H

#include <QtWidgets>
#include "toolcore.h"

class ToolVector : public ToolCore
{
    Q_OBJECT
    bool isClicked, isStart, isStop;
    int pointStartX, pointStartY, pointBeginX, pointBeginY, pointEndX, pointEndY;
    bool directMod;
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

    void uptool_selectColor1();
    void uptool_selectColor2();
    QPoint directCoordinates(int x1, int y1, int x2, int y2);
public:
    ToolVector(QImage *display, QColor *selectedColor1, QColor *selectedColor2, QToolBar *uptool, QStatusBar *statusInfo, int *penWidth, QWidget *parent = nullptr);
    void isSelect();
public slots:
    void vectorClose();
    void vectorUp();
};

#endif // TOOLVECTOR_H
