#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QCloseEvent>

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

private:
    Ui::MainWindow *ui;
    int height, width;
    QGridLayout *gridLayout;
};

#endif // MAINWINDOW_H
