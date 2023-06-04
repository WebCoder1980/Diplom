#ifndef DIALOGCREATEFILE_H
#define DIALOGCREATEFILE_H

#include <QtWidgets>

class DialogCreateFile : public QDialog
{
    Q_OBJECT
    QVBoxLayout *mainBoxLayout;
    QHBoxLayout *fieldWidth, *fieldHeight;
    QLabel *labelMain, *labelWidthDisplay, *labelHeightDisplay;
    QLineEdit *leWidthDisplay, *leHeightDisplay;
    QPushButton *pbOk;
    int *widthPtr, *heightPtr;
public:
    DialogCreateFile(int *widthPtr, int *heightPtr, QWidget *parent = nullptr);
    ~DialogCreateFile();
public slots:
    void fOk();
};

#endif // DIALOGCREATEFILE_H
