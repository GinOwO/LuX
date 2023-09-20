#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mazesolve.h"

#include <QMainWindow>
#include <QGridLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setDimen(const int&h, const int&w);
    void createGrid();
    void toggleBlock(int row, int col);
    void loadGrid(const VSS&arr);

private slots:
    void on_actionSave_triggered();

    void on_actionReset_triggered();

    void on_actionReload_triggered();

    void on_actionDFS_triggered();

    void on_actionBFS_triggered();

    void on_actionFlood_Fill_triggered();

private:
    Ui::MainWindow *ui;
    int height, width;
    QGridLayout *gridLayout;

    VSS getArray();
    bool reload;
    VSS reload_arr;
    void solveMaze(int);
};

#endif // MAINWINDOW_H
