#include <QMainWindow>
#include <QGridLayout>

#define VS std::vector<std::string>
#define VSS std::vector<VS>

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

    void on_actionStart_triggered();

    void on_actionReload_triggered();

private:
    Ui::MainWindow *ui;
    int height, width;
    QGridLayout *gridLayout;
    VSS getArray();
    bool reload;
    VSS reload_arr;
};

#endif // MAINWINDOW_H
