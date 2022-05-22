#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "field.h"
#include "timer.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
        Q_OBJECT
    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        Field* f;
        SessionTimer* timer;
    private:
        Ui::MainWindow *ui;
};
#endif
