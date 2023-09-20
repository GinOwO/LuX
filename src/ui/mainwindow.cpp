#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "mazesolve.h"
#include "slots.h"

#include <QCloseEvent>
#include <QInputDialog>
#include <QMessageBox>
#include <QGridLayout>
#include <QPushButton>
#include <QSize>

#include <stdexcept>
#include <vector>
#include <string>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    gridLayout = new QGridLayout;
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(gridLayout);
    setCentralWidget(centralWidget);
    for (int i = 0; i < height; i++) for (int j = 0; j < width; j++) gridLayout->itemAtPosition(i, j)->widget();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::setDimen(const int&h, const int&w){
    this->height = h; this->width = w;
}

void MainWindow::createGrid(){
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    this->reload = false;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Slots *button = new Slots;
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setMinimumSize(15,15);
            gridLayout->addWidget(button, i, j);

        }
    }
}

void MainWindow::loadGrid(const VSS&arr){
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    this->reload = true;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            auto c = arr[i][j];
            Slots *button = new Slots;
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setMinimumSize(15,15);
            if (c=="W") button->toggleBlock();
            else if(c=="S") button->toggleStart();
            else if(c=="E") button->toggleEnd();
            gridLayout->addWidget(button, i, j);
        }
    this->reload_arr=arr;
}

VSS MainWindow::getArray(){
    VSS arr;
    bool start = false, end = false;
    for (int i = 0; i < height; i++){
        VS i_arr;
        for (int j = 0; j < width; j++) {
            auto item = gridLayout->itemAtPosition(i, j);
            if (item){
                auto slot = qobject_cast<Slots*>(item->widget());
                if (slot){
                    if (slot->isStart()){
                        if(start) throw std::invalid_argument("There can only be one start");
                        start=true; i_arr.push_back("S");
                    }
                    else if(slot->isEnd())i_arr.push_back("E"), end=true;
                    else if(slot->isWall()) i_arr.push_back("W");
                    else i_arr.push_back(".");
                }
            }
        }
        arr.push_back(i_arr);
    }
    if(!start || !end) throw std::invalid_argument("Missing Start or Finish");
    return arr;
}

void MainWindow::on_actionReset_triggered(){
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            auto item = gridLayout->itemAtPosition(i, j);
            if (item){
                auto slot = qobject_cast<Slots*>(item->widget());
                if (slot) slot->reset();
            }
        }
}

void MainWindow::on_actionSave_triggered(){
    VSS arr;
    try {arr = getArray();}
    catch(const std::invalid_argument& e){
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
    if(MazeSolve::saveArr(MazeSolve::getDir(), arr))
        QMessageBox::information(this,"SUCCESS","Saved successfully");
    else
        QMessageBox::critical(this,"Error","Some Error occurred, try again with a different location");
}

void MainWindow::on_actionStart_triggered(){
    auto arr = this->getArray();
    bool pass = MazeSolve::solve(height, width, arr);
    if (!pass){
        QMessageBox::critical(this, "Path Not Found", "No solution for this maze exists");
        return;
    }
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            auto item = gridLayout->itemAtPosition(i, j);
            if (item){
                auto slot = qobject_cast<Slots*>(item->widget());
                if (slot){
                    if (slot->isStart()||slot->isEnd()||slot->isWall()) continue;
                    slot->reset();
                    if (arr[i][j]=="T") slot->toggleSoln();
                }
            }
        }

}


void MainWindow::on_actionReload_triggered(){
    if(!this->reload){
        QMessageBox::critical(this, "Error", "Can only be used if maze is loaded from file");
        return;
    }
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            auto item = gridLayout->itemAtPosition(i, j);
            if (item){
                auto slot = qobject_cast<Slots*>(item->widget());
                if (slot){
                    slot->reset();
                    if(this->reload_arr[i][j]=="W") slot->toggleBlock();
                    else if(this->reload_arr[i][j]=="S") slot->toggleStart();
                    else if(this->reload_arr[i][j]=="E") slot->toggleEnd();
                }
            }
        }

}

