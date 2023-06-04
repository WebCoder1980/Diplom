#include "mainmenu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainMenu *w = new MainMenu();
    w->show();
    return a.exec();
}
