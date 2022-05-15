#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "field.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Field* f = new Field;
    for (int i = 0; i < f->fX; ++i){
        for (int j = 0; j < f->fY; ++j){
            ui->Field->addWidget(&(f->Tiles[i][j]), i, j, 1, 1);
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

