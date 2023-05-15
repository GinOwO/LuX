#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "slots.h"

#include <QGridLayout>
#include <QPushButton>
#include <QCloseEvent>
#include <QSize>


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

