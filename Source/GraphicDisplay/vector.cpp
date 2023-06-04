#include "vector.h"

ToolVector::ToolVector(QImage *display, QColor *selectedColor1, QColor *selectedColor2, QToolBar *uptool, QStatusBar *statusInfo, int *penWidth, QWidget *parent) : ToolCore(display, selectedColor1, selectedColor2, uptool, statusInfo, penWidth, parent)
{
    isClicked = isStart = isStop = 0;
    pointStartX = pointStartY = pointBeginX = pointBeginY = pointEndX = pointEndY = 0;
    directMod = 0;
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

/*virtual*/ void ToolVector::mousePressEvent(QMouseEvent *event) {
    isClicked = 1;
    if(!isStart) {
        pointStartX = pointBeginX = pointEndX = event->x();
        pointStartY = pointBeginY = pointEndY = event->y();
        isStart = 1;
    }
    else {
        pointEndX = event->x();
        pointEndY = event->y();
    }
    update();
}

/*virtual*/ void ToolVector::mouseMoveEvent(QMouseEvent *event) {
    if(isStart) {
        pointEndX = event->x();
        pointEndY = event->y();
        update();
    }
}

/*virtual*/ void ToolVector::paintEvent(QPaintEvent *) {
    if(isStart) {
        if(isClicked) {
            qDebug() << pointBeginX << pointBeginY << " - " << pointEndX << pointEndY;
            QPainter paint(display);
            paint.setPen(QPen(*selectedColor1, *penWidthPtr, Qt::SolidLine, Qt::SquareCap));
            if(pointBeginX == pointEndX && pointBeginY == pointEndY) {
                paint.drawPoint(pointBeginX, pointBeginY);
            }
            else {
                if(!directMod) paint.drawLine(pointBeginX, pointBeginY, pointEndX, pointEndY);
                else paint.drawLine(QPoint(pointBeginX, pointBeginY), directCoordinates(pointBeginX, pointBeginY, pointEndX, pointEndY));
            }
            paint.end();
            paint.begin(this);
            paint.drawImage(0, 0, *display);
            isClicked = 0;
            if(directMod) {
                QPoint point = directCoordinates(pointBeginX, pointBeginY, pointEndX, pointEndY);
                pointBeginX = pointEndX = point.x();
                pointBeginY = pointEndY = point.y();
            }
            else {
                pointBeginX = pointEndX;
                pointBeginY = pointEndY;
            }
        }
        else {
            QPainter paint(this);
            paint.setPen(QPen(*selectedColor1, *penWidthPtr, Qt::SolidLine, Qt::SquareCap));
            paint.drawImage(0, 0, *display);
            if(pointBeginX == pointEndX && pointBeginY == pointEndY) {
                paint.drawPoint(pointBeginX, pointBeginY);
            }
            else {
                if(!directMod) paint.drawLine(pointBeginX, pointBeginY, pointEndX, pointEndY);
                else paint.drawLine(QPoint(pointBeginX, pointBeginY), directCoordinates(pointBeginX, pointBeginY, pointEndX, pointEndY));
            }
        }
    }
    else {
        QPainter paint(this);
        paint.drawImage(0, 0, *display);
    }
}

void ToolVector::isSelect() {
    uptool->clear();
    QPixmap *icon = new QPixmap(50, 50);
    QPainter paint(icon);
    paint.fillRect(0, 0, 50, 50, qRgba(0, 0, 0, 255)) ;
    paint.fillRect(0+1, 0+1, 50-2, 50-2, *selectedColor1);
    paint.end();
    uptool->addAction(QIcon(), "Закрыть", this, &ToolVector::vectorClose);
    uptool->addAction(QIcon(), "Поднять перо", this, &ToolVector::vectorUp);
    uptool->addAction(QIcon(":/Icons/Width.png"), "Размер пера", this, &ToolVector::uptool_selectResize);
    uptool->addAction(QIcon(*icon), "Цвет", this, &ToolVector::uptool_selectColor1);
}

void ToolVector::vectorClose() {
    pointEndX = pointStartX;
    pointEndY = pointStartY;
    isClicked = 1;
    repaint();
    isClicked = isStart = 0;
    pointStartX = pointStartY = pointBeginX = pointBeginY = pointEndX = pointEndY = 0;
}

void ToolVector::vectorUp() {
    isClicked = isStart = 0;
    pointStartX = pointStartY = pointBeginX = pointBeginY = pointEndX = pointEndY = 0;
    update();
}

void ToolVector::uptool_selectColor1() {
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
void ToolVector::uptool_selectColor2() {
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

/*virtual*/ void ToolVector::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Shift) { directMod = 1; update(); }
}

/*virtual*/ void ToolVector::keyReleaseEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Shift) { directMod = 0; update(); }
}

QPoint ToolVector::directCoordinates(int x1, int y1, int x2, int y2) {
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
