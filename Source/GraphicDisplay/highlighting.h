#ifndef TOOLHIGHLIGHTING_H
#define TOOLHIGHLIGHTING_H

#include <QtWidgets>
#include "toolcore.h"

class ToolHighlighting : public ToolCore
{
    Q_OBJECT
    short clicksNum;
    QPoint pointBegin, pointEnd, pointCursor;
    QImage *highlightingZone;
    bool directMod;
    void reset();
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    QPoint directCoordinates(int x1, int y1, int x2, int y2);

    enum state { OFF, HIGHLIGHTING, CLEAR, MOVING, SET };
public:
    ToolHighlighting(QImage *display, QToolBar *uptool, QStatusBar *statusInfo, QWidget *parent = nullptr);
    void isSelect();
};

#endif // TOOLHIGHLIGHTING_H
