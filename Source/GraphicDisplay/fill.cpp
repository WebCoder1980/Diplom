#include "fill.h"

ToolFill::ToolFill(QImage *display, QColor *selectedColor1, QColor *selectedColor2, QToolBar *uptool, QStatusBar *statusInfo, QWidget *parent) : ToolCore(display, selectedColor1, selectedColor2, uptool, statusInfo, nullptr, parent)
{
    this->display = display;
    colorTolerance = 1;
    fillColor = qRgb(255, 0, 0);
}

/*virtual*/ void ToolFill::mousePressEvent(QMouseEvent *event) {
    if(event->buttons() == Qt::LeftButton) fillColor = *selectedColor1;
    else if(event->buttons() == Qt::RightButton) fillColor = *selectedColor2;
    else return;
    seachColor = display->pixelColor(event->x(), event->y());
    paintProcess(event->pos());
    update();
}
void ToolFill::paintProcess(QPoint point) {
    QStack<QPoint> pixels;
    if(seachColor == fillColor) return;
    pixels.push(point);
    while(!pixels.empty()) {
        if(display->pixelColor(pixels.top()) == seachColor) {
            QPoint w, e;
            w = e = pixels.top();
            while(display->pixelColor(w) == seachColor && display->pixelColor(w.x()-1, w.y()) == seachColor) w.setX(w.x()-1);
            while(display->pixelColor(e) == seachColor && display->pixelColor(e.x()+1, e.y()) == seachColor) e.setX(e.x()+1);
            for(int ind = w.x(); ind <= e.x(); ind++) display->setPixelColor(ind, w.y(), fillColor);
            for(int width = w.x(); width <= e.x(); width++) {
                if(display->pixelColor(width, w.y()-1) == seachColor) { pixels.push(QPoint(width, w.y()-1)); }
                if(display->pixelColor(width, w.y()+1) == seachColor) { pixels.push(QPoint(width, w.y()+1)); }
            }
        }
        else pixels.pop();
    }
    update();
}

/*virtual*/ void ToolFill::paintEvent(QPaintEvent *event) {
    QPainter paint(this);
    paint.drawImage(0, 0, *display);
    paint.end();
}

void ToolFill::isSelect() {
    uptool->clear();
    QPixmap *icon = new QPixmap(50, 50);
    QPainter paint(icon);
    paint.fillRect(0, 0, 50, 50, qRgba(0, 0, 0, 255)) ;
    paint.fillRect(0+1, 0+1, 50-2, 50-2, *selectedColor1);
    paint.end();
    uptool->addAction(QIcon(*icon), "Цвет(1)", this, &ToolCore::uptool_selectColor1);
    icon = new QPixmap(50, 50);
    paint.begin(icon);
    paint.fillRect(0, 0, 50, 50, qRgba(0, 0, 0, 255)) ;
    paint.fillRect(0+1, 0+1, 50-2, 50-2, *selectedColor2);
    paint.end();
    uptool->addAction(QIcon(*icon), "Цвет(2)", this, &ToolCore::uptool_selectColor2);
}
