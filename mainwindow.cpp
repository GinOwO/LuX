#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "slots.h"
#include "mazesolve.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QGridLayout>
#include <QPushButton>
#include <QCloseEvent>
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
    for (int row = 0; row < height; row++) for (int col = 0; col < width; col++) gridLayout->itemAtPosition(row, col)->widget();
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

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            Slots *button = new Slots;
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setMinimumSize(15,15);
            gridLayout->addWidget(button, row, col);

        }
    }
}

void MainWindow::loadGrid(const VSS&arr){
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    for (int row = 0; row < height; row++)
        for (int col = 0; col < width; col++) {
            auto c = arr[row][col];
            Slots *button = new Slots;
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setMinimumSize(15,15);
            if (c=="W") button->toggleBlock();
            else if(c=="S") button->toggleStart();
            else if(c=="E") button->toggleEnd();
            gridLayout->addWidget(button, row, col);
        }
}

VSS MainWindow::getArray(){
    VSS arr;
    bool start = false, end = false;
    for (int row = 0; row < height; row++){
        VS row_arr;
        for (int col = 0; col < width; col++) {
            auto item = gridLayout->itemAtPosition(row, col);
            if (item){
                auto slot = qobject_cast<Slots*>(item->widget());
                if (slot){
                    if (slot->getStart()){
                        if(start) throw std::invalid_argument("There can only be one start");
                        start=true; row_arr.push_back("S");
                    }
                    else if(slot->getEnd())row_arr.push_back("E"), end=true;
                    else if(slot->getWall()) row_arr.push_back("W");
                    else row_arr.push_back(".");
                }
            }
        }
        arr.push_back(row_arr);
    }
    if(!start || !end) throw std::invalid_argument("Missing Start or Finish");
    return arr;
}

void MainWindow::on_actionReset_triggered(){
    for (int row = 0; row < height; row++)
        for (int col = 0; col < width; col++) {
            auto item = gridLayout->itemAtPosition(row, col);
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
    std::string dir = MazeSolve::getDir();




}

