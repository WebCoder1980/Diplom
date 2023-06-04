#include "dialogcreatefile.h"

DialogCreateFile::DialogCreateFile(int *widthPtr, int *heightPtr, QWidget *parent) : QDialog(parent)
{
    mainBoxLayout = new QVBoxLayout();
    fieldWidth = new QHBoxLayout();
    fieldHeight = new QHBoxLayout();
    labelMain = new QLabel("Установить размеры изображения:");
    labelWidthDisplay = new QLabel("Ширина: ");
    labelHeightDisplay = new QLabel("Высота: ");
    leWidthDisplay = new QLineEdit();
    leHeightDisplay = new QLineEdit();
    pbOk = new QPushButton(QIcon(), "Создать");
    this->widthPtr = widthPtr;
    this->heightPtr = heightPtr;

    //this:
    QObject::connect(pbOk, &QPushButton::clicked, this, &DialogCreateFile::fOk);
    leWidthDisplay->setValidator(new QIntValidator(1, 2000));
    leHeightDisplay->setValidator(new QIntValidator(1, 2000));
    mainBoxLayout->addWidget(labelMain);
    mainBoxLayout->addLayout(fieldWidth);
    mainBoxLayout->addLayout(fieldHeight);
    mainBoxLayout->addWidget(pbOk);
    fieldWidth->addWidget(labelWidthDisplay);
    fieldWidth->addWidget(leWidthDisplay);
    fieldHeight->addWidget(labelHeightDisplay);
    fieldHeight->addWidget(leHeightDisplay);

    setLayout(mainBoxLayout);
    setWindowTitle("Создание изображения...");
    show();
}

DialogCreateFile::~DialogCreateFile() {

}

void DialogCreateFile::fOk() {
    *widthPtr = leWidthDisplay->text().toInt();
    *heightPtr = leHeightDisplay->text().toInt();
    accept();
}
