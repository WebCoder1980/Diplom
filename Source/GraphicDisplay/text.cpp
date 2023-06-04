#include "text.h"

ToolText::ToolText(QImage *display, QColor *selectedColor1, QColor *selectedColor2, QToolBar *uptool, QStatusBar *statusInfo, int *penWidth, QWidget *parent) : ToolCore(display, selectedColor1, selectedColor2, uptool, statusInfo, penWidth, parent)
{
    pointBeginX = pointBeginY = pointEndX = pointEndY = 0;
    paintText = 0;
    this->statusInfo = statusInfo;
    this->display = display;
    this->uptool = uptool;
    this->selectedColor1 = selectedColor1;
    this->selectedColor2 = selectedColor2;
    this->penWidthPtr = penWidth;
}

/*virtual*/ void ToolText::mousePressEvent(QMouseEvent *event) {
    manualPaint = 1;
    if(event->button() == Qt::LeftButton) pressedLeftButton = 1;
    else pressedLeftButton = 0;
    pointBeginX = pointEndX = event->x();
    pointBeginY = pointEndY = event->y();
    update();
}
/*virtual*/ void ToolText::mouseMoveEvent(QMouseEvent *event) {
    pointEndX = event->x();
    pointEndY = event->y();
    update();
}
/*virtual*/ void ToolText::mouseReleaseEvent(QMouseEvent *event) {
    paintText = 1;
    repaint();
    paintText = manualPaint = 0;
    pointBeginX = pointEndX = 0;
    pointBeginY = pointEndY = 0;
}
/*virtual*/ void ToolText::paintEvent(QPaintEvent *) {
    if(manualPaint) {
        if(pressedLeftButton) {
            if(paintText) {
                bool rs;
                paintText = 0;
                QString text = QInputDialog::getText(this, "Добавить текст", "Введите текст для добавления на картинку:", QLineEdit::EchoMode::Normal, QString(), &rs);
                paintText = 1;
                if(rs) {
                    QPainter paint(display);
                    paint.setPen(QPen(*selectedColor1, *penWidthPtr, Qt::SolidLine, Qt::PenCapStyle::RoundCap, Qt::PenJoinStyle::RoundJoin));
                    QFont fontinfo;
                    fontinfo.setPixelSize(*penWidthPtr <= 10 ? 10 : *penWidthPtr);
                    paint.setFont(fontinfo);
                    paint.drawText(pointBeginX, pointBeginY, pointEndX-pointBeginX, pointEndY-pointBeginY, 0, text);
                    paint.end();
                    paint.begin(this);
                    paint.drawImage(0, 0, *display);
                }
                else return;
            }
            else {
                QPainter paint(this);
                paint.setPen(QPen(Qt::red, 3, Qt::DashLine, Qt::PenCapStyle::RoundCap, Qt::PenJoinStyle::RoundJoin));
                paint.drawImage(0, 0, *display);
                paint.drawRect(pointBeginX, pointBeginY, pointEndX-pointBeginX, pointEndY-pointBeginY);
            }
        }
        else {
            if(paintText) {
                bool rs;
                paintText = 0;
                QString text = QInputDialog::getText(this, "Добавить текст", "Введите текст для добавления на картинку:", QLineEdit::EchoMode::Normal, QString(), &rs);
                paintText = 1;
                if(rs) {
                    QPainter paint(display);
                    paint.setPen(QPen(*selectedColor2, *penWidthPtr, Qt::SolidLine, Qt::PenCapStyle::RoundCap, Qt::PenJoinStyle::RoundJoin));
                    QFont fontinfo;
                    fontinfo.setPixelSize(*penWidthPtr <= 10 ? 10 : *penWidthPtr);
                    paint.setFont(fontinfo);
                    paint.drawText(pointBeginX, pointBeginY, pointEndX-pointBeginX, pointEndY-pointBeginY, 0, text);
                    paint.end();
                    paint.begin(this);
                    paint.drawImage(0, 0, *display);
                }
                else return;
            }
            else {
                QPainter paint(this);
                paint.setPen(QPen(Qt::red, 3, Qt::DashLine, Qt::PenCapStyle::RoundCap, Qt::PenJoinStyle::RoundJoin));
                paint.drawImage(0, 0, *display);
                paint.drawRect(pointBeginX, pointBeginY, pointEndX-pointBeginX, pointEndY-pointBeginY);
            }
        }
    }
    else {
        QPainter paint(this);
        paint.drawImage(0, 0, *display);
    }
}
