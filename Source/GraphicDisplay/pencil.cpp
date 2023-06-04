#include "pencil.h"

ToolPencil::ToolPencil(QImage *display, QColor *selectedColor1, QColor *selectedColor2, QToolBar *uptool, QStatusBar *statusInfo, int *penWidthPtr, QWidget *parent) : ToolCore(display, selectedColor1, selectedColor2, uptool, statusInfo, penWidthPtr, parent)
{
    pointBeginX = pointBeginY = pointEndX = pointEndY = 0;
    pressedLeftButton = 0;
    this->display = display;
    this->selectedColor1 = selectedColor1;
    this->selectedColor2 = selectedColor2;
    this->uptool = uptool;
    this->penWidthPtr = penWidthPtr;
}

/*virtual*/ void ToolPencil::mousePressEvent(QMouseEvent *event) {
    manualPaint = 1;
    if(event->buttons() == Qt::LeftButton) {
        pointBeginX = pointEndX = event->x();
        pointBeginY = pointEndY = event->y();
        display->setPixelColor(pointBeginX, pointBeginY, *selectedColor1);
        pressedLeftButton = 1;
    }
    else {
        pointBeginX = pointEndX = event->x();
        pointBeginY = pointEndY = event->y();
        display->setPixelColor(pointBeginX, pointBeginY, *selectedColor2);
        pressedLeftButton = 0;
    }
    update();

}
/*virtual*/ void ToolPencil::mouseMoveEvent(QMouseEvent *event) {
    manualPaint = 1;
    if(event->buttons() == Qt::LeftButton) {
        if(pointBeginX == pointEndX) {
            pointEndX = event->x();
            pointEndY = event->y();
        }
        display->setPixelColor(pointBeginX, pointBeginY, *selectedColor1);
        pressedLeftButton = 1;
    }
    else {
        if(pointBeginX == pointEndX) {
            pointEndX = event->x();
            pointEndY = event->y();
        }
        display->setPixelColor(pointBeginX, pointBeginY, *selectedColor2);
        pressedLeftButton = 0;
    }
    update();
}
/*virtual*/ void ToolPencil::mouseReleaseEvent(QMouseEvent *event) {

}
/*virtual*/ void ToolPencil::paintEvent(QPaintEvent *) {
    if(pressedLeftButton) {
        if(manualPaint) {
            QPainter paint(display);
            paint.setPen(QPen(*selectedColor1, *penWidthPtr, Qt::SolidLine, Qt::PenCapStyle::RoundCap, Qt::PenJoinStyle::RoundJoin));
            if(!isrepaint) {
                if(!(pointBeginX == pointEndX && pointBeginY == pointEndY)) paint.drawLine(pointBeginX, pointBeginY, pointEndX, pointEndY);
                else { paint.drawPoint(pointBeginX, pointBeginY); }
            }
            paint.end();
            paint.begin(this);
            paint.drawImage(0, 0, *display);
            paint.end();
            pointBeginX = pointEndX;
            pointBeginY = pointEndY;
        }
        else {
            QPainter paint(this);
            paint.drawImage(0, 0, *display);
            paint.end();
        }
    }
    else {
        if(manualPaint) {
            QPainter paint(display);
            paint.setPen(QPen(*selectedColor2, *penWidthPtr, Qt::SolidLine, Qt::PenCapStyle::RoundCap, Qt::PenJoinStyle::RoundJoin));
            if(!isrepaint) {
                if(!(pointBeginX == pointEndX && pointBeginY == pointEndY)) paint.drawLine(pointBeginX, pointBeginY, pointEndX, pointEndY);
                else { paint.drawPoint(pointBeginX, pointBeginY); }
            }
            paint.end();
            paint.begin(this);
            paint.drawImage(0, 0, *display);
            paint.end();
            pointBeginX = pointEndX;
            pointBeginY = pointEndY;
        }
        else {
            QPainter paint(this);
            paint.drawImage(0, 0, *display);
            paint.end();
        }
    }
    manualPaint = 0;
}
