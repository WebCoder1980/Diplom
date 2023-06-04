#include "toolcore.h"

ToolCore::ToolCore(QImage *display, QColor *selectedColor1, QColor *selectedColor2, QToolBar *uptool, QStatusBar *statusInfo, int *penWidthPtr, QWidget *parent) : QWidget(parent)
{
    pressedLeftButton = 0;
    this->display = display;
    this->selectedColor1 = selectedColor1;
    this->selectedColor2 = selectedColor2;
    isrepaint = 0;
    this->uptool = uptool;
    this->statusInfo = statusInfo;
    this->penWidthPtr = penWidthPtr;
    manualPaint = 0;
    iconSize = 50;
    for(int ind = 0; ind < display->width(); ind++) {
        for(int jnd = 0; jnd < display->height(); jnd++) {
            display->setPixelColor(ind, jnd, Qt::white);
        }
    }
    resize(display->width(), display->height());
}

ToolCore& ToolCore::operator=(ToolCore& right) {
    return right;
}

/*virtual*/ void ToolCore::mousePressEvent(QMouseEvent *event) { }
/*virtual*/ void ToolCore::mouseMoveEvent(QMouseEvent *event) { }
/*virtual*/ void ToolCore::mouseReleaseEvent(QMouseEvent *event) { }
/*virtual*/ void ToolCore::paintEvent(QPaintEvent *) { }
/*virtual*/ void ToolCore::resizeEvent(QResizeEvent *event) { }

void ToolCore::isSelect() {
    uptool->clear();
    QPixmap *icon = new QPixmap(50, 50);
    QPainter paint(icon);
    paint.fillRect(0, 0, 50, 50, qRgba(0, 0, 0, 255)) ;
    paint.fillRect(0+1, 0+1, 50-2, 50-2, *selectedColor1);
    paint.end();    
    uptool->addAction(QIcon(":/Icons/Width.png"), "Размер пера", this, &ToolCore::uptool_selectResize);
    uptool->addAction(QIcon(*icon), "Цвет(1)", this, &ToolCore::uptool_selectColor1);
    icon = new QPixmap(50, 50);
    paint.begin(icon);
    paint.fillRect(0, 0, 50, 50, qRgba(0, 0, 0, 255)) ;
    paint.fillRect(0+1, 0+1, 50-2, 50-2, *selectedColor2);
    paint.end();
    uptool->addAction(QIcon(*icon), "Цвет(2)", this, &ToolCore::uptool_selectColor2);

}

void ToolCore::uptool_selectResize() {
    bool npressedCancel;
    int width = QInputDialog::getInt(this, "Выбор размера инструмента:", "Размер в пикселях:", *penWidthPtr, 0, 1000, 1, &npressedCancel);
    if(!npressedCancel) {
        return;
    }
    *penWidthPtr = width;
}
void ToolCore::uptool_selectColor1() {
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
void ToolCore::uptool_selectColor2() {
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
