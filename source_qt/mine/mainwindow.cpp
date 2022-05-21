#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "field.h"
//#include <QDebug>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    f = new Field(45, 45, 250, this); // 1: xSize, 2: ySize, 3: mines, 4: parent ptr
    ui->hlayout->addWidget(f->gmbutton, 1, Qt::AlignCenter);
    ui->hlayout->addWidget(f->tbutton, Qt::AlignRight);
    for (int i = 0; i < f->fX; ++i){
        for (int j = 0; j < f->fY; ++j){
            ui->Field->addWidget(&(f->Tiles[i][j]), i, j, Qt::AlignCenter);
        }
    }
    //setGeometry(ui->Field->geometry().x(), ui->Field->geometry().y(), ui->Field->geometry().width(), ui->Field->geometry().height());
}
MainWindow::~MainWindow()
{
    delete f;
    delete ui;
}

