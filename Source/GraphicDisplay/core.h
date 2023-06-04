#ifndef GRAPHICDISPLAYCORE_H
#define GRAPHICDISPLAYCORE_H

#include <QtWidgets>
#include "GraphicDisplay/pencil.h"
#include "GraphicDisplay/brush.h"
#include "GraphicDisplay/erasser.h"
#include "GraphicDisplay/fill.h"
#include "GraphicDisplay/ruller.h"
#include "GraphicDisplay/highlighting.h"
#include "GraphicDisplay/figures.h"
#include <GraphicDisplay/vector.h>
#include "GraphicDisplay/text.h"
#include "GraphicDisplay/insertphoto.h"

class GraphicDisplayCore : public QObject
{
    Q_OBJECT
public:
    QSize imageSize;
    QImage *display;
    QColor *selectedColor1, *selectedColor2;
    QVector<QColor> colorList;
    int pointBeginX, pointBeginY, pointEndX, pointEndY;
    int *toolIndexPtr;
    QToolBar *uptool;
    QStatusBar *statusInfo;
    int penWidth;

    enum selectToolIndex { PENCIL, BRUSH, ERASSER, RULLER, HIGHLIGHTING, FIGURES, VECTOR, TEXT };

    QWidget *checkedToolPtr;
    ToolPencil *widgetPencil;
    ToolBrush *widgetBrush;
    ToolErasser *widgetErasser;
    ToolFill *widgetFill;
    ToolRuller *widgetRuller;
    ToolHighlighting *widgetHighlighting;
    ToolFigures *widgetFigures;
    ToolVector *widgetVector;
    ToolText *widgetText;
    ToolInsertPhoto *widgetInsertPhoto;
    GraphicDisplayCore(int *toolIndexPtr, QToolBar *uptool, QStatusBar *statusInfo, QWidget *parent = nullptr);
};

#endif // GRAPHICDISPLAYCORE_H
