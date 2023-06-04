#include "ruller.h"

ToolRuller::ToolRuller(QImage *display, QToolBar *uptool, QStatusBar *statusInfo, QWidget *parent) : ToolCore(display, nullptr, nullptr, uptool, statusInfo, nullptr, parent)
{
    pointBeginX = pointBeginY = pointEndX = pointEndY = 0;
    this->statusInfo = statusInfo;
    this->display = display;
    this->uptool = uptool;
    isPressed = 0;
}

/*virtual*/ void ToolRuller::mousePressEvent(QMouseEvent *event) {
    isPressed = 1;
    pointBeginX = pointEndX = event->x();
    pointBeginY = pointEndY = event->y();
    statusInfo->showMessage(QString("p1(%1, %2), p2(%3, %4). Расстояние: %5.").arg(pointBeginX).arg(pointBeginY).arg(pointEndX).arg(pointBeginY).arg(sqrt((pointBeginX-pointEndX)*(pointBeginX-pointEndX)+(pointBeginY-pointEndY)*(pointBeginY-pointEndY))));
    update();
}
/*virtual*/ void ToolRuller::mouseMoveEvent(QMouseEvent *event) {
    pointEndX = event->x();
    pointEndY = event->y();
    update();
    statusInfo->showMessage(QString("p1(%1, %2), p2(%3, %4). Расстояние: %5.").arg(pointBeginX).arg(pointBeginY).arg(pointEndX).arg(pointEndY).arg(sqrt((pointBeginX-pointEndX)*(pointBeginX-pointEndX)+(pointBeginY-pointEndY)*(pointBeginY-pointEndY))));
    update();
}
/*virtual*/ void ToolRuller::mouseReleaseEvent(QMouseEvent *event) {
    pointBeginX = pointBeginY = pointEndX = pointEndY = 0;
    statusInfo->showMessage("");
    update();
    isPressed = 0;
}
/*virtual*/ void ToolRuller::paintEvent(QPaintEvent *) {
    QPainter paint(this);
    paint.setPen(QPen(Qt::black, 3));
    paint.drawImage(0, 0, *display);
    if(isPressed) paint.drawLine(pointBeginX, pointBeginY, pointEndX, pointEndY);
}

void ToolRuller::isSelect() {
    uptool->clear();
}
