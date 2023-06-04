#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include "dialogcreatefile.h"
#include "GraphicDisplay/core.h"

class MainMenu : public QMainWindow
{
    Q_OBJECT
    QMenuBar *mainMenu;
    QMenu *menuFile;
    QToolBar *mainTools;
    enum selectToolIndex { PENCIL, BRUSH, ERASSER, FILL, RULLER, HIGHLIGHTING, FIGURES, VECTOR, TEXT, INSERTPHOTO };
    int selectedtoolindex;
    QToolBar *upTool;
    QStatusBar *statusInfo;

    QString fileWay;

private:
    virtual void closeEvent(QCloseEvent *event);

public:
    GraphicDisplayCore *graphicDisplay;
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

public slots:
    void selectPensil();
    void selectBrush();
    void selectEraser();
    void selectFill();
    void selectRuller();
    void selectHighlighting();
    void selectFigures();
    void selectVector();
    void selectText();
    void selectInsertPhoto();

    void createFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void closeFile();
    void addPhotoInDisplay();
    void exitProgram();
};
#endif // MAINMENU_H
