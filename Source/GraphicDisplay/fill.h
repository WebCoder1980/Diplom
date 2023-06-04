#ifndef TOOLFILL_H
#define TOOLFILL_H

#include <QtWidgets>
#include "toolcore.h"

class ToolFill : public ToolCore
{
    Q_OBJECT
    QImage *display;
    int colorTolerance;
    QColor seachColor, fillColor;
    void paintProcess(QPoint point);
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
public:
    void isSelect();
    ToolFill(QImage *display, QColor *selectedColor1, QColor *selectedColor2, QToolBar *uptool, QStatusBar *statusInfo, QWidget *parent = nullptr);
};

#endif // TOOLFILL_H
