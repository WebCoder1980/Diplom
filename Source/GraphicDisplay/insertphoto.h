#ifndef TOOLINSERTPHOTO_H
#define TOOLINSERTPHOTO_H

#include <QtWidgets>
#include "toolcore.h"

class ToolInsertPhoto : public ToolCore
{
    Q_OBJECT
    QString insertPhotoWay;
    QImage insertPhotoFile;
    int mouseCoordinateX, mouseCoordinateY;
    bool mouseClick;
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
public:
    ToolInsertPhoto(QImage *display, QToolBar *uptool, QStatusBar *statusInfo, QWidget *parent = nullptr);
    void isSelect();

public slots:
    void insertPhoto();
};

#endif // TOOLINSERTPHOTO_H
