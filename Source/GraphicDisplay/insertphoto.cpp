#include "insertphoto.h"

ToolInsertPhoto::ToolInsertPhoto(QImage *display, QToolBar *uptool, QStatusBar *statusInfo, QWidget *parent) : ToolCore(display, nullptr, nullptr, uptool, statusInfo, nullptr, parent)
{
    this->display = display;
    this->uptool = uptool;
    this->statusInfo = statusInfo;
    insertPhotoWay = "";
    setMouseTracking(true);
    mouseCoordinateX = mouseCoordinateY = 0;
    mouseClick = false;
}

/*virtual*/ void ToolInsertPhoto::mousePressEvent(QMouseEvent *event) {
    mouseClick = true;
    update();
}

/*virtual*/ void ToolInsertPhoto::mouseMoveEvent(QMouseEvent *event) {
    if(insertPhotoWay != "") {
        mouseCoordinateX = event->x();
        mouseCoordinateY = event->y();
        update();
    }
}

/*virtual*/ void ToolInsertPhoto::paintEvent(QPaintEvent *event) {
    if(insertPhotoWay != "") {
        if(!mouseClick) {
            QPainter paint(this);
            paint.setBrush(QBrush(QColor(0, 0, 0, 128)));
            paint.drawImage(0, 0, *display);
            paint.drawImage(mouseCoordinateX, mouseCoordinateY, insertPhotoFile);
        }
        else {
            QPainter paint(display);
            paint.drawImage(mouseCoordinateX, mouseCoordinateY, insertPhotoFile);
            paint.end();
            paint.begin(this);
            paint.drawImage(0, 0, *display);
            mouseClick = 0;
            insertPhotoWay = "";
        }
    }
    else {
        QPainter paint(this);
        paint.drawImage(0, 0, *display);
    }
}

void ToolInsertPhoto::isSelect() {
    uptool->clear();
    uptool->addAction(QIcon(), "Вставить фото", this, &ToolInsertPhoto::insertPhoto);
}

void ToolInsertPhoto::insertPhoto() {
    if(insertPhotoWay == "") {
        QString buf_way = QFileDialog::getOpenFileName(this, "Добавить фото из...", "", "Images (*.png *.jpg *.bmp)");
        if(buf_way != "") {
            insertPhotoWay = buf_way;
            insertPhotoFile.load(insertPhotoWay);
        }
    }
}
