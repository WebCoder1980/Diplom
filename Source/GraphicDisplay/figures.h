#ifndef TOOLFIGURES_H
#define TOOLFIGURES_H

#include <QtWidgets>
#include "toolcore.h"

class ToolFigures : public ToolCore
{
    Q_OBJECT
    QStringList figureList;
    int figureSelectIndex;
    short figureIsDraw;
    QPoint pointStart, pointEnd;
    bool directMod;
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    void uptool_selectColor1();
    void uptool_selectColor2();
    QPoint directCoordinates(int x1, int y1, int x2, int y2);
public:
    enum figuresIndexes { RECTANGLE, ROUNDEDRECTANGLE, ELLIPSE, TRIANGLE };
    ToolFigures(QImage *display, QColor *selectedColor1, QColor *selectedColor2, QToolBar *uptool, QStatusBar *statusInfo, int *penWidth, QWidget *parent = nullptr);
    void isSelect();
    void figureSelect();
};

#endif // TOOLFIGURES_H

struct FillInTheArea {

};
