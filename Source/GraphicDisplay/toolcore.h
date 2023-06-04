#ifndef TOOLCORE_H
#define TOOLCORE_H

#include <QtWidgets>

class ToolCore : public QWidget
{
public:
    bool pressedLeftButton;
    QImage *display;
    QColor *selectedColor1, *selectedColor2;
    bool isrepaint;
    QToolBar *uptool;
    QStatusBar *statusInfo;
    int *penWidthPtr;
    bool manualPaint;
    int iconSize;
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    ToolCore(QImage *display, QColor *selectedColor1, QColor *selectedColor2, QToolBar *uptool, QStatusBar *statusInfo, int *penWidthPtr, QWidget *parent = nullptr);
    void isSelect();
    ToolCore& operator=(ToolCore& right);
public slots:
    void uptool_selectResize();
    void uptool_selectColor1();
    void uptool_selectColor2();
};

#endif // TOOLCORE_H
