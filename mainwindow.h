#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QCloseEvent>

#define VS std::vector<std::string>
#define VSS std::vector<VS>

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

private:
    Ui::MainWindow *ui;
    int height, width;
    QGridLayout *gridLayout;
    VSS getArray();
};

#endif // MAINWINDOW_H
