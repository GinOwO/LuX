#include "startwindow.h"
#include "./ui_startwindow.h"
#include "mainwindow.h"
#include "mazesolve.h"

#include <QMessageBox>
#include <QDebug>
#include <QCloseEvent>
#include <QMainWindow>

StartWindow::StartWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::StartWindow){
    ui->setupUi(this);
}

StartWindow::~StartWindow(){
    delete ui;
}

void StartWindow::on_start_button_clicked(){
    QString hstr = ui->height_inp->text();
    QString wstr = ui->width_inp->text();
    bool flag[2];
    const int h = hstr.toInt(flag), w = wstr.toInt(flag+1);
    if (flag[0]&&flag[1]&&h>0&&w>0){
        this->hide();
        auto Window = new MainWindow;
        Window->setDimen(h,w);
        Window->createGrid();
        Window->show();
    }else{
        QMessageBox::critical(this, "Invalid input", "Use only positive integers for height/width.");
    }
}

void StartWindow::on_loadButton_clicked(){
    this->hide();
    int h, w;
    auto Window = new MainWindow;
    Window->setDimen(h,w);
    Window->loadGrid(MazeSolve::loadArr(MazeSolve::getDir()));
    Window->show();
}

