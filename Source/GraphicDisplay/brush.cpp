#include "brush.h"

ToolBrush::ToolBrush(QImage *display, QColor *selectedColor1, QColor *selectedColor2, QToolBar *uptool, QStatusBar *statusInfo, int *penWidthPtr, QWidget *parent) : ToolPencil(display, selectedColor1, selectedColor2, uptool, statusInfo, penWidthPtr, parent)
{

}

/*virtual*/ void ToolBrush::paintEvent(QPaintEvent *event) {
    if(pressedLeftButton) {
        QPainter paint(display);
        paint.setRenderHint(QPainter::Antialiasing, true);
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
        QPainter paint(display);
        paint.setRenderHint(QPainter::Antialiasing, true);
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
}
