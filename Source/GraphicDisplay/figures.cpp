#include "figures.h"

ToolFigures::ToolFigures(QImage *display, QColor *selectedColor1, QColor *selectedColor2, QToolBar *uptool, QStatusBar *statusInfo, int *penWidthPtr, QWidget *parent) : ToolCore(display, selectedColor1, selectedColor2, uptool, statusInfo, penWidthPtr, parent)
{
    figureList << "Квадрат" << "Квадрат с закруглёнными краями" << "Эллипс" << "Треугольник";
    figureSelectIndex = 0;
    figureIsDraw = 0;
    directMod = 0;
    setFocusPolicy(Qt::StrongFocus);
}

void ToolFigures::isSelect() {
    uptool->clear();
    QPixmap *icon = new QPixmap(50, 50);
    QPainter paint(icon);
    paint.fillRect(0, 0, 50, 50, qRgba(0, 0, 0, 255)) ;
    paint.fillRect(0+1, 0+1, 50-2, 50-2, *selectedColor1);
    paint.end();
    uptool->addAction(QIcon(), QString("Выбрать фигуру (%1)").arg(figureList.at(figureSelectIndex)), this, &ToolFigures::figureSelect);
    uptool->addAction(QIcon(":/Icons/Width.png"), "Размер обводки", this, &ToolFigures::uptool_selectResize);
    uptool->addAction(QIcon(*icon), "Цвет обводки", this, &ToolFigures::uptool_selectColor1);
    icon = new QPixmap(50, 50);
    paint.begin(icon);
    paint.fillRect(0, 0, 50, 50, qRgba(0, 0, 0, 255)) ;
    paint.fillRect(0+1, 0+1, 50-2, 50-2, *selectedColor2);
    paint.end();
    uptool->addAction(QIcon(*icon), "Цвет заполнения", this, &ToolFigures::uptool_selectColor2);
}

void ToolFigures::figureSelect() {
    QString buf_figure = QInputDialog::getItem(this, "Выбрать фигуру", "Выберите фигуру из списка:", figureList);
    for(int ind = 0; ind < figureList.count(); ind++) {
        if(figureList.at(ind) == buf_figure) {
            figureSelectIndex = ind;
            isSelect();
        }
    }
}

/*virtual*/ void ToolFigures::mousePressEvent(QMouseEvent *event) {
    figureIsDraw = 1;
    pointStart.setX(event->x());
    pointStart.setY(event->y());
    update();
}

/*virtual*/ void ToolFigures::mouseMoveEvent(QMouseEvent *event) {
    pointEnd.setX(event->x());
    pointEnd.setY(event->y());
    update();
}

/*virtual*/ void ToolFigures::mouseReleaseEvent(QMouseEvent *event) {
    figureIsDraw = 2;
    pointEnd.setX(event->x());
    pointEnd.setY(event->y());
    repaint();
    figureIsDraw = 0;
}

/*virtual*/ void ToolFigures::paintEvent(QPaintEvent *) {
    QPoint point = directCoordinates(pointStart.x(), pointStart.y(), pointEnd.x(), pointEnd.y());
    if(figureIsDraw == 0) {
        QPainter paint(this);
        paint.drawImage(0, 0, *display);
    }
    else if(figureIsDraw == 1) {
        QPainter paint(this);
        paint.drawImage(0, 0, *display);
        paint.setPen(QPen(*selectedColor1, *penWidthPtr, Qt::SolidLine, Qt::PenCapStyle::RoundCap, Qt::PenJoinStyle::RoundJoin));
        paint.setBrush(*selectedColor2);
        if(directMod) {
            switch (figureSelectIndex) {
            case 0:
                paint.drawRect(QRect(pointStart, point));
                break;
            case 1:
                paint.drawRoundedRect(QRect(pointStart, point), 30, 30);
                break;
            case 2:
                paint.drawEllipse(QRect(pointStart, point));
                break;
            case 3:
                QPoint p1(pointStart.x(), point.y());
                QPoint p2(point);
                QPoint p3((pointStart.x()+point.x())/2, pointStart.y());
                QVector<QPoint> lines;
                lines << p1 << p2 << p3;
                paint.drawPolygon(QPolygon(lines));
                break;
            }
        }
        else {
            switch (figureSelectIndex) {
            case 0:
                paint.drawRect(QRect(pointStart, pointEnd));
                break;
            case 1:
                paint.drawRoundedRect(QRect(pointStart, pointEnd), 30, 30);
                break;
            case 2:
                paint.drawEllipse(QRect(pointStart, pointEnd));
                break;
            case 3:
                QPoint p1(pointStart.x(), pointEnd.y());
                QPoint p2(pointEnd);
                QPoint p3((pointStart.x()+pointEnd.x())/2, pointStart.y());
                QVector<QPoint> lines;
                lines << p1 << p2 << p3;
                paint.drawPolygon(QPolygon(lines));
                break;
            }
        }
    }
    else if(figureIsDraw == 2) {
        QPainter paint(display);
        paint.setPen(QPen(*selectedColor1, *penWidthPtr, Qt::SolidLine, Qt::PenCapStyle::RoundCap, Qt::PenJoinStyle::RoundJoin));
        paint.setBrush(*selectedColor2);
        if(directMod) {
            switch (figureSelectIndex) {
            case 0:
                paint.drawRect(QRect(pointStart, point));
                break;
            case 1:
                paint.drawRoundedRect(QRect(pointStart, point), 30, 30);
                break;
            case 2:
                paint.drawEllipse(QRect(pointStart, point));
                break;
            case 3:
                QPoint p1(pointStart.x(), point.y());
                QPoint p2(point);
                QPoint p3((pointStart.x()+point.x())/2, pointStart.y());
                QVector<QPoint> lines;
                lines << p1 << p2 << p3;
                paint.drawPolygon(QPolygon(lines));
                break;
            }
        }
        else {
            qDebug() << "=";
            switch (figureSelectIndex) {
            case 0:
                paint.drawRect(QRect(pointStart, pointEnd));
                break;
            case 1:
                paint.drawRoundedRect(QRect(pointStart, pointEnd), 30, 30);
                break;
            case 2:
                paint.drawEllipse(QRect(pointStart, pointEnd));
                break;
            case 3:
                QPoint p1(pointStart.x(), pointEnd.y());
                QPoint p2(pointEnd);
                QPoint p3((pointStart.x()+pointEnd.x())/2, pointStart.y());
                QVector<QPoint> lines;
                lines << p1 << p2 << p3;
                paint.drawPolygon(QPolygon(lines));
                break;
            }
        }
        paint.end();
        paint.begin(this);
        paint.drawImage(0, 0, *display);
    }
}

void ToolFigures::uptool_selectColor1() {
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
void ToolFigures::uptool_selectColor2() {
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

QPoint ToolFigures::directCoordinates(int x1, int y1, int x2, int y2) {
    double direction = (atan2(y2 - y1, x2 - x1) / acos(-1) * 180)+90;
    if(direction > 180 && direction <= 270) direction = -(270-direction+90); //170 в 100; 160 в 110
    int DC = 180/2;
    if(direction < -DC) { int xd=x2-x1,yd=y2-y1; xd = abs(xd); yd = abs(yd); return +xd > +yd ? QPoint(x1-xd, y1+xd) : QPoint(x1-yd, y1+yd); }
    else if(direction < 0) { int xd=x2-x1,yd=y2-y1; xd = abs(xd); yd = abs(yd); return +xd > +yd ? QPoint(x1-xd, y1-xd) : QPoint(x1-yd, y1-yd); }
    else if(direction < DC) { int xd=x2-x1,yd=y2-y1; xd = abs(xd); yd = abs(yd); return +xd > +yd ? QPoint(x1+xd, y1-xd) : QPoint(x1+yd, y1-yd); }
    else if(direction <= DC*2) { int xd=x2-x1,yd=y2-y1; xd = abs(xd); yd = abs(yd); return +xd > +yd ? QPoint(x1+xd, y1+xd) : QPoint(x1+yd, y1+yd); }
    return QPoint(0, 0);
}

/*virtual*/ void ToolFigures::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Shift) { directMod = 1; update(); }
}

/*virtual*/ void ToolFigures::keyReleaseEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Shift) { directMod = 0; update(); }
}
