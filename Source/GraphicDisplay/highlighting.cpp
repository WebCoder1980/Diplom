#include "highlighting.h"

ToolHighlighting::ToolHighlighting(QImage *display, QToolBar *uptool, QStatusBar *statusInfo, QWidget *parent) : ToolCore(display, nullptr, nullptr, uptool, statusInfo, nullptr, parent)
{
    clicksNum = OFF;
    pointBegin = pointEnd = pointCursor = QPoint(0, 0);
    directMod = 0;
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

/*virtual*/ void ToolHighlighting::mousePressEvent(QMouseEvent *event) {
    if(clicksNum == OFF) {
        pointBegin.setX(event->x());
        pointBegin.setY(event->y());
        pointEnd = pointBegin;
        clicksNum = HIGHLIGHTING;
        update();
    }

    else if(clicksNum == MOVING) {
        pointCursor.setX(event->x());
        pointCursor.setY(event->y());
        clicksNum = SET;
        update();
    }
}

/*virtual*/ void ToolHighlighting::mouseMoveEvent(QMouseEvent *event) {
    if(clicksNum == HIGHLIGHTING) {
        pointEnd.setX(event->x());
        pointEnd.setY(event->y());
        update();
    }

    if(clicksNum == MOVING) {
        pointCursor.setX(event->x());
        pointCursor.setY(event->y());
        update();
    }
}

/*virtual*/ void ToolHighlighting::mouseReleaseEvent(QMouseEvent *event) {
    if(clicksNum == HIGHLIGHTING) {
        pointEnd.setX(event->x());
        pointEnd.setY(event->y());
        int width = pointEnd.x()-pointBegin.x()+1, height = pointEnd.y()-pointBegin.y()+1;
        highlightingZone = new QImage(width, height, QImage::Format::Format_RGB32);
        for(int ind = 0; ind < width; ind++) {
            for(int jnd = 0; jnd < height; jnd++) {
                highlightingZone->setPixelColor(ind, jnd, display->pixel(pointBegin.x()+ind, pointBegin.y()+jnd));
            }
        }
        clicksNum = CLEAR;
        update();
    }
}

/*virtual*/ void ToolHighlighting::paintEvent(QPaintEvent *) {
    if(clicksNum == OFF) {
        QPainter paint(this);
        paint.drawImage(0, 0, *display);
        paint.end();
    }

    else if(clicksNum == HIGHLIGHTING) {
        QPainter paint(this);
        paint.drawImage(0, 0, *display);
        paint.setPen(QPen(QBrush(qRgba(255, 0, 0, 128)), 3, Qt::PenStyle::DashLine));
        if(directMod) paint.drawRect(QRect(pointBegin, directCoordinates(pointBegin.x(), pointBegin.y(), pointEnd.x(), pointEnd.y())));
        else paint.drawRect(QRect(pointBegin, pointEnd));
        paint.end();
    }
    else if(clicksNum == CLEAR) {
        QPainter paint(display);
        paint.fillRect(QRect(pointBegin, pointEnd), Qt::white);
        paint.end();
        paint.begin(this);
        paint.drawImage(0, 0, *display);
        paint.drawImage(pointCursor, *highlightingZone);
        paint.end();
        clicksNum = MOVING;
    }

    else if(clicksNum == MOVING) {
        QPainter paint(this);
        paint.drawImage(0, 0, *display);
        paint.drawImage(pointCursor, *highlightingZone);
    }

    else if(clicksNum == SET) {
        QPainter paint(display);
        paint.drawImage(pointCursor, *highlightingZone);
        paint.end();
        paint.begin(this);
        paint.drawImage(0, 0, *display);
        paint.end();
        reset();
    }
}

void ToolHighlighting::isSelect() {
    uptool->clear();
}

void ToolHighlighting::reset() {
    clicksNum = OFF;
    pointBegin = pointEnd = pointCursor = QPoint(0, 0);
    delete highlightingZone;
}

/*virtual*/ void ToolHighlighting::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Shift) { directMod = 1; update(); }
}

/*virtual*/ void ToolHighlighting::keyReleaseEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Shift) { directMod = 0; update(); }
}

QPoint ToolHighlighting::directCoordinates(int x1, int y1, int x2, int y2) {
    double direction = (atan2(y2 - y1, x2 - x1) / acos(-1) * 180)+90;
    if(direction > 180 && direction <= 270) direction = -(270-direction+90); //170 в 100; 160 в 110
    int DC = 180/4;
    if(direction < -DC*3.5) { return QPoint(x1, y2);}
    else if(direction < -DC*2.5) { int xd=x2-x1,yd=y2-y1; xd = abs(xd); yd = abs(yd); return +xd > +yd ? QPoint(x1-xd, y1+xd) : QPoint(x1-yd, y1+yd); }
    else if(direction < -DC*1.5) { return QPoint(x2, y1); }
    else if(direction < -DC*0.5) { int xd=x2-x1,yd=y2-y1; xd = abs(xd); yd = abs(yd); return +xd > +yd ? QPoint(x1-xd, y1-xd) : QPoint(x1-yd, y1-yd); }
    else if(direction < DC*0.5) { return QPoint(x1, y2); }
    else if(direction < DC*1.5) { int xd=x2-x1,yd=y2-y1; xd = abs(xd); yd = abs(yd); return +xd > +yd ? QPoint(x1+xd, y1-xd) : QPoint(x1+yd, y1-yd); }
    else if(direction < DC*2.5) { return QPoint(x2, y1);}
    else if(direction < DC*3.5) { int xd=x2-x1,yd=y2-y1; xd = abs(xd); yd = abs(yd); return +xd > +yd ? QPoint(x1+xd, y1+xd) : QPoint(x1+yd, y1+yd); }
    else if(direction <= DC*4.0) { return QPoint(x1, y2); }
    return QPoint(0, 0);
}
