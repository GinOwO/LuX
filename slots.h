#ifndef SLOTS_H
#define SLOTS_H

#include <QPushButton>
#include <QMouseEvent>

#define setWhite() setStyleSheet("background-color: white;")
#define setBlack() setStyleSheet("background-color: black;")
#define setGreen() setStyleSheet("background-color: green;")
#define setBlue() setStyleSheet("background-color: blue;")
#define setRed() setStyleSheet("background-color: red;")

class Slots : public QPushButton{
    Q_OBJECT
public:
    explicit Slots(QWidget *parent = nullptr);
    void toggleBlock();
    void toggleSoln();
    void toggleStart();
    void toggleEnd();
    bool isStart(){return start;}
    bool isEnd(){return end;}
    bool isWall(){return toggled;}
    void reset(){
        soln = start = end = toggled = false;
        setWhite();
    }

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    bool toggled, soln, start, end;
};

#endif
