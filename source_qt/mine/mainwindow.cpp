#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "field.h"
//#include <QDebug>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    f = new Field(45, 45, 255, this); // 1: xSize, 2: ySize, 3: mines, 4: parent ptr
    timer = new SessionTimer(parent); // id: 0
    ui->hlayout->addWidget(f->tbutton, Qt::AlignRight);
    ui->hlayout->addWidget(f->gmbutton, Qt::AlignCenter);
    ui->hlayout->addWidget(timer, Qt::AlignLeft);
    connect(f, SIGNAL(start()), timer, SLOT(slstart()), Qt::DirectConnection);
    connect(f, SIGNAL(finish()), timer, SLOT(slstop()), Qt::DirectConnection);
    connect(f, SIGNAL(finishinst()), timer, SLOT(setzero()), Qt::DirectConnection);
    for (int i = 0; i < f->fX; ++i){
        for (int j = 0; j < f->fY; ++j){
            ui->Field->addWidget(&(f->Tiles[i][j]), i, j, Qt::AlignCenter);
        }
    }
}
MainWindow::~MainWindow()
{
    delete f;
    QObject::killTimer(0);
    delete ui;
}

