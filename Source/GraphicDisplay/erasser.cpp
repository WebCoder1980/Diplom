#include "erasser.h"

ToolErasser::ToolErasser(QImage *display, QToolBar *uptool, QStatusBar *statusInfo, int *penWidthPtr, QWidget *parent) : ToolCore(display, nullptr, nullptr, uptool, statusInfo, penWidthPtr, parent)
{
     pointBeginX = pointBeginY = pointEndX = pointEndY = 0;
     this->display = display;
     this->penWidthPtr = penWidthPtr;
}

/*virtual*/ void ToolErasser::mousePressEvent(QMouseEvent *event) {
    manualPaint = 1;
    if(event->buttons() == Qt::LeftButton) {
        pointBeginX = pointEndX = event->x();
        pointBeginY = pointEndY = event->y();
        pressedLeftButton = 1;
    }
    else {
        pointBeginX = pointEndX = event->x();
        pointBeginY = pointEndY = event->y();
        pressedLeftButton = 0;
    }
    update();

}
/*virtual*/ void ToolErasser::mouseMoveEvent(QMouseEvent *event) {
    manualPaint = 1;
    if(event->buttons() == Qt::LeftButton) {
        if(pointBeginX == pointEndX) {
            pointEndX = event->x();
            pointEndY = event->y();
        }
        pressedLeftButton = 1;
    }
    else {
        if(pointBeginX == pointEndX) {
            pointEndX = event->x();
            pointEndY = event->y();
        }
        pressedLeftButton = 0;
    }
    update();
}
/*virtual*/ void ToolErasser::mouseReleaseEvent(QMouseEvent *event) {

}

/*virtual*/ void ToolErasser::paintEvent(QPaintEvent *event) {
    if(manualPaint) {
        QPainter paint(display);
        paint.setPen(QPen(Qt::white, *penWidthPtr, Qt::SolidLine, Qt::PenCapStyle::RoundCap, Qt::PenJoinStyle::RoundJoin));
        if(!isrepaint) {
            if(!(pointBeginX == pointEndX && pointBeginY == pointEndY)) paint.drawLine(pointBeginX, pointBeginY, pointEndX, pointEndY);
            else { paint.drawPoint(pointBeginX, pointBeginY); }
            paint.end();
            paint.begin(this);
            paint.drawImage(0, 0, *display);
            paint.end();
            pointBeginX = pointEndX;
            pointBeginY = pointEndY;
        }
    }
    else {
        QPainter paint(this);
        paint.drawImage(0, 0, *display);
        paint.end();
    }
    manualPaint = 0;
}

void ToolErasser::isSelect() {
    uptool->clear();
    uptool->addAction(QIcon(":/Icons/Width.png"), "Размер пера", this, &ToolCore::uptool_selectResize);
}

void ToolErasser::uptool_selectColor1() {
    QColor buf;
    {
        QColor color = QColorDialog::getColor(*selectedColor1, this, "Выбор цвета(1)");
        //Если цвет не выбран (нажата Cancel)
        if(!color.isValid()) {
            return;
        }
        buf = color;
    }
    *selectedColor1 = buf;
    isSelect();
}
void ToolErasser::uptool_selectColor2() {
    {
        QColor color = QColorDialog::getColor(*selectedColor2, this, "Выбор цвета(2)");
        //Если цвет не выбран (нажата Cancel)
        if(!color.isValid()) {
            return;
        }
        *selectedColor2 = color;
        isSelect();
    }
}
