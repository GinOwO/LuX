#ifndef SLOTS_H
#define SLOTS_H

#include <QPushButton>
#include <QMouseEvent>

class Slots : public QPushButton{
    Q_OBJECT
public:
    explicit Slots(QWidget *parent = nullptr);
    void toggleBlock();
private:
    bool toggled, soln, start, end;
};

#endif
