#include "slots.h"
#include <QMenu>
#include <QAction>

Slots::Slots(QWidget *parent) : QPushButton(parent){
    setStyleSheet("background-color: white;");
    soln = start = end = toggled = false;
    connect(this, &Slots::clicked, this, &Slots::toggleBlock);
}

void Slots::toggleBlock(){
    toggled = !toggled;
    if (toggled) {
        setStyleSheet("background-color: red;");
    } else {
        setStyleSheet("background-color: white;");
    }
}
