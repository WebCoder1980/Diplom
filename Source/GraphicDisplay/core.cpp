#include "core.h"

GraphicDisplayCore::GraphicDisplayCore(int *toolIndexPtr, QToolBar *uptool, QStatusBar *statusInfo, QWidget *parent) : QObject(parent)
{
    //Инициализация:
    imageSize = QSize(800, 600);
    display = new QImage(imageSize.width(), imageSize.height(), QImage::Format_RGB32);
    selectedColor1 = nullptr;
    selectedColor2 = nullptr;
    colorList << QColor(0, 0, 0) << QColor(255, 0, 0) << QColor(0, 255, 0) << QColor(0, 255, 0) << QColor(0, 0, 255) << QColor(255, 255, 255);
    selectedColor1 = &colorList[0];
    selectedColor2 = &colorList[colorList.count()-1];
    pointBeginX = pointBeginY = pointEndX = pointEndY = 0;
    this->toolIndexPtr = toolIndexPtr;
    this->uptool = uptool;
    this->statusInfo = statusInfo;
    penWidth = 3;

    widgetPencil = new ToolPencil(display, selectedColor1, selectedColor2, uptool, statusInfo, &penWidth);
    widgetBrush = new ToolBrush(display, selectedColor1, selectedColor2, uptool, statusInfo, &penWidth);
    widgetErasser = new ToolErasser(display, uptool, statusInfo, &penWidth);
    widgetFill = new ToolFill(display, selectedColor1, selectedColor2, uptool, statusInfo);
    widgetRuller = new ToolRuller(display, uptool, statusInfo);
    widgetHighlighting = new ToolHighlighting(display, uptool, statusInfo);
    widgetFigures = new ToolFigures(display, selectedColor1, selectedColor2, uptool, statusInfo, &penWidth);
    widgetVector = new ToolVector(display, selectedColor1, selectedColor2, uptool, statusInfo, &penWidth);
    widgetText = new ToolText(display, selectedColor1, selectedColor2, uptool, statusInfo, &penWidth);
    widgetInsertPhoto = new ToolInsertPhoto(display, uptool, statusInfo);
    checkedToolPtr = widgetPencil;
    //this:
}
