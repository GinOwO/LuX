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
    if (flag[0]&&flag[1]&&h>2&&w>2){
        auto Window = new MainWindow;
        Window->setDimen(h,w);
        Window->createGrid();
        this->hide();
        Window->show();
    }else{
        QMessageBox::critical(this, "Invalid input", "Height and Width must be greater than 2");
    }
}

void StartWindow::on_loadButton_clicked(){
    auto arr = MazeSolve::loadArr(MazeSolve::getDir());
    if(arr.empty()||arr[0].empty()){
        QMessageBox::critical(this, "Invalid input", "Please check the path of the input file");
        return;
    }
    int h=arr.size(), w=arr[0].size();
    if(h<3||w<3){
        QMessageBox::critical(this, "Invalid input", "Height and Width must be greater than 2");
        return;
    }
    auto Window = new MainWindow;
    Window->setDimen(h,w);
    Window->loadGrid(arr);
    this->hide();
    Window->show();
}

