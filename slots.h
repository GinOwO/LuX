#ifndef SLOTS_H
#define SLOTS_H

#include <QPushButton>
#include <QMouseEvent>

#define setWhite() setStyleSheet("background-color: white;")
#define setBlack() setStyleSheet("background-color: black;")
#define setRed() setStyleSheet("background-color: red;")
#define setGreen() setStyleSheet("background-color: green;")


class Slots : public QPushButton{
    Q_OBJECT
public:
    explicit Slots(QWidget *parent = nullptr);
    void toggleBlock();
    void toggleSoln();
    void toggleStart();
    void toggleEnd();
    bool getStart(){return start;}
    bool getEnd(){return end;}
    bool getWall(){return toggled;}
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
