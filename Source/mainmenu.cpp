#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
{
    //Инициализация:
    upTool = new QToolBar("Меню инструмета");
    mainMenu = new QMenuBar();
    menuFile = new QMenu("Файл");
    statusInfo = new QStatusBar();
    graphicDisplay = new GraphicDisplayCore(&selectedtoolindex, upTool, statusInfo);
    mainTools = new QToolBar("Базовые инструметы");
    selectedtoolindex = 0;
    fileWay = "";
    //mainMenu:
    mainMenu->addMenu(menuFile);

    mainMenu->addAction("Добавить фото", this, &MainMenu::selectInsertPhoto);

    menuFile->addAction(QIcon(), "Создать...", this, &MainMenu::createFile);
    menuFile->addAction(QIcon(), "Открыть...", this, &MainMenu::openFile);
    menuFile->addSeparator();
    menuFile->addAction(QIcon(), "Сохранить", this, &MainMenu::saveFile);
    menuFile->addAction(QIcon(), "Сохранить как...", this, &MainMenu::saveAsFile);
    menuFile->addSeparator();
    menuFile->addAction(QIcon(), "Закрыть файл", this, &MainMenu::closeFile);
    menuFile->addAction(QIcon(), "Выйти", this, &MainMenu::exitProgram);

    //mainTools:
    mainTools->addAction(QIcon(":/Icons/Pencil.png"), "Карандаш", this, &MainMenu::selectPensil);
    mainTools->addAction(QIcon(":/Icons/Erasser.png"), "Ластик", this, &MainMenu::selectEraser);
    mainTools->addAction(QIcon(":/Icons/Ruller.png"), "Линейка", this, &MainMenu::selectRuller);
    mainTools->addAction(QIcon(":/Icons/Fill.png"), "Заполнение", this, &MainMenu::selectFill);
    mainTools->addAction(QIcon(":/Icons/Highlighting"), "Выделение", this, &MainMenu::selectHighlighting);
    mainTools->addAction(QIcon(":/Icons/Figures.png"), "Фигуры", this, &MainMenu::selectFigures);
    mainTools->addAction(QIcon(":/Icons/Vector.png"), "Вектора", this, &MainMenu::selectVector);
    mainTools->addAction(QIcon(":/Icons/Text.png"), "Текст", this, &MainMenu::selectText);

    //this:
    setStyleSheet("QMainWindow {background: #CCCCCC;}");
    setCentralWidget(graphicDisplay->checkedToolPtr);
    centralWidget()->setMinimumSize(800, 600);
    resize(800, 600);

    setMenuBar(mainMenu);
    addToolBar(Qt::LeftToolBarArea, mainTools);
    addToolBar(Qt::TopToolBarArea, upTool);
    setStatusBar(statusInfo);
    selectPensil();
}

MainMenu::~MainMenu()
{

}

/*virtual*/ void MainMenu::closeEvent(QCloseEvent *event) {
    QMessageBox *question = new QMessageBox(QMessageBox::Icon::Question, "Выход из программы", "Сохранить файл перед закрытием?", QMessageBox::StandardButton::Ok | QMessageBox::StandardButton::No | QMessageBox::StandardButton::Cancel);
    int answer = question->exec();
    if(answer == QMessageBox::StandardButton::Ok) {
        saveFile();
    }
    else if(answer == QMessageBox::StandardButton::No);
    else event->ignore();
}

//Слоты выбора базового инструмета:

void MainMenu::selectPensil() {
    if(auto* p=centralWidget()){p->setParent(nullptr);}
    setCentralWidget(graphicDisplay->widgetPencil);
    graphicDisplay->widgetPencil->isSelect();
    selectedtoolindex = PENCIL;
}

void MainMenu::selectBrush() {
    if(auto* p=centralWidget()){ p->setParent(nullptr); }
    setCentralWidget(graphicDisplay->widgetBrush);
    graphicDisplay->widgetBrush->isSelect();
    selectedtoolindex = BRUSH;
}

void MainMenu::selectEraser() {
    if(auto* p=centralWidget()){p->setParent(nullptr);}
    setCentralWidget(graphicDisplay->widgetErasser);
    graphicDisplay->widgetErasser->isSelect();
    selectedtoolindex = ERASSER;
}

void MainMenu::selectFill() {
    if(auto* p=centralWidget()){p->setParent(nullptr);}
    setCentralWidget(graphicDisplay->widgetFill);
    graphicDisplay->widgetFill->isSelect();
    selectedtoolindex = FILL;
}

void MainMenu::selectRuller() {
    if(auto* p=centralWidget()){p->setParent(nullptr);}
    setCentralWidget(graphicDisplay->widgetRuller);
    graphicDisplay->widgetRuller->isSelect();
    selectedtoolindex = RULLER;
}
void MainMenu::selectHighlighting() {
    if(auto* p=centralWidget()){p->setParent(nullptr);}
    setCentralWidget(graphicDisplay->widgetHighlighting);
    graphicDisplay->widgetHighlighting->isSelect();
    selectedtoolindex = HIGHLIGHTING;
}
void MainMenu::selectFigures() {
    if(auto* p=centralWidget()){p->setParent(nullptr);}
    setCentralWidget(graphicDisplay->widgetFigures);
    graphicDisplay->widgetFigures->isSelect();
    selectedtoolindex = FIGURES;
}
void MainMenu::selectVector() {
    if(auto* p=centralWidget()){p->setParent(nullptr);}
    setCentralWidget(graphicDisplay->widgetVector);
    graphicDisplay->widgetVector->isSelect();
    selectedtoolindex = VECTOR;
}

void MainMenu::selectText() {
    if(auto* p=centralWidget()){p->setParent(nullptr);}
    setCentralWidget(graphicDisplay->widgetText);
    graphicDisplay->widgetText->isSelect();
    selectedtoolindex = TEXT;
}

void MainMenu::selectInsertPhoto() {
    if(auto* p=centralWidget()){p->setParent(nullptr);}
    setCentralWidget(graphicDisplay->widgetInsertPhoto);
    graphicDisplay->widgetInsertPhoto->isSelect();
    selectedtoolindex = INSERTPHOTO;
}

void MainMenu::createFile() {
    if(fileWay == "") {
        int width, height;
        DialogCreateFile dialog(&width, &height, this);
        if(dialog.exec() == QDialog::Accepted) {
           *graphicDisplay->display = graphicDisplay->display->scaled(width, height);
           centralWidget()->resize(width, height);
           centralWidget()->setMinimumSize(width, height);
           resize(width, height);
           for(int ind = 0; ind < graphicDisplay->display->width(); ind++) {
               for(int jnd = 0; jnd < graphicDisplay->display->height(); jnd++) {
                   graphicDisplay->display->setPixelColor(ind, jnd, Qt::white);
               }
           }
        }
    }
    else {
        QMessageBox *question = new QMessageBox(QMessageBox::Icon::Question, "Создание изображения", "Сохранить предыдущую фотографию перед закрытием?", QMessageBox::StandardButton::Ok | QMessageBox::StandardButton::No | QMessageBox::StandardButton::Cancel, this);
        int answer = question->exec();
        if(answer == QMessageBox::StandardButton::Ok) {
            saveFile();
            int width, height;
            DialogCreateFile dialog(&width, &height, this);
            if(dialog.exec() == QDialog::Accepted) {
               *graphicDisplay->display = graphicDisplay->display->scaled(width, height);
               centralWidget()->resize(width, height);
               for(int ind = 0; ind < graphicDisplay->display->width(); ind++) {
                   for(int jnd = 0; jnd < graphicDisplay->display->height(); jnd++) {
                       graphicDisplay->display->setPixelColor(ind, jnd, Qt::white);
                   }
               }
            }
        }
        else if(answer == QMessageBox::StandardButton::No) {
            int width, height;
            DialogCreateFile dialog(&width, &height, this);
            if(dialog.exec() == QDialog::Accepted) {
               *graphicDisplay->display = graphicDisplay->display->scaled(width, height);
               centralWidget()->resize(width, height);
               for(int ind = 0; ind < graphicDisplay->display->width(); ind++) {
                   for(int jnd = 0; jnd < graphicDisplay->display->height(); jnd++) {
                       graphicDisplay->display->setPixelColor(ind, jnd, Qt::white);
                   }
               }
            }
        }
        delete question;
    }
}
void MainMenu::openFile() {
    QMessageBox *question = new QMessageBox(QMessageBox::Icon::Question, "Создание изображения", "Сохранить предыдущую фотографию перед закрытием?", QMessageBox::StandardButton::Ok | QMessageBox::StandardButton::No | QMessageBox::StandardButton::Cancel, this);
    int answer = question->exec();
    if(answer == QMessageBox::StandardButton::Ok) {
        saveFile();
        QString buf_way = QFileDialog::getOpenFileName(this, "Открыть файл...", "", "Images (*.png, *.jpg, *.bmp)");
        if(buf_way != "") {
            graphicDisplay->display->load(buf_way);
            graphicDisplay->checkedToolPtr->update();
            fileWay = buf_way;
        }
    }
    else if(answer == QMessageBox::StandardButton::No) {
        QString buf_way = QFileDialog::getOpenFileName(this, "Открыть файл...", "", "Images (*.png *.jpg *.bmp)");
        if(buf_way != "") {
            graphicDisplay->display->load(buf_way);
            graphicDisplay->checkedToolPtr->update();
            fileWay = buf_way;
        }
    }
    delete question;
}

void MainMenu::saveFile() {
    if(fileWay != "") graphicDisplay->display->save(fileWay.replace("/", "//"));
    else saveAsFile();
}

void MainMenu::saveAsFile() {
    QString buf_way = QFileDialog::getSaveFileName(this, "Сохранить как...", "", "*.png;;*.jpg;;*.bmp)");
    if(buf_way != "") {
        graphicDisplay->display->save(buf_way);
        fileWay = buf_way;
    }
}

void MainMenu::closeFile() {
    fileWay = "";
    for(int ind = 0; ind < graphicDisplay->display->width(); ind++) {
        for(int jnd = 0; jnd < graphicDisplay->display->height(); jnd++) {
            graphicDisplay->display->setPixelColor(ind, jnd, Qt::white);
        }
    }
    graphicDisplay->checkedToolPtr->update();
}

void MainMenu::addPhotoInDisplay() {

}

void MainMenu::exitProgram() {
    QMessageBox *question = new QMessageBox(QMessageBox::Icon::Question, "Выход из программы", "Сохранить файл перед закрытием?", QMessageBox::StandardButton::Ok | QMessageBox::StandardButton::No | QMessageBox::StandardButton::Cancel);
    int answer = question->exec();
    if(answer == QMessageBox::StandardButton::Ok) {
        saveFile();
    }
    else if(answer == QMessageBox::StandardButton::No);
    else return;
    close();
}
