#include "slots.h"
#include <QMenu>
#include <QAction>

Slots::Slots(QWidget *parent) : QPushButton(parent){
    this->reset();
    connect(this, &Slots::clicked, this, &Slots::toggleBlock);
}

void Slots::toggleBlock(){
    toggled = !toggled;
    if (toggled) setBlack();
    else setWhite();
}

void Slots::contextMenuEvent(QContextMenuEvent *event){
    this->reset();; QMenu menu(this);
    QAction *startslot = new QAction("Toggle Start", this);
    QAction *endslot = new QAction("Toggle Finish", this);
    connect(startslot, &QAction::triggered, this, &Slots::toggleStart);
    connect(endslot, &QAction::triggered, this, &Slots::toggleEnd);
    menu.addAction(startslot); menu.addAction(endslot);
    menu.exec(event->globalPos());
}

void Slots::toggleStart(){
    start = !start;
    if(start) setRed();
    else setWhite();
}

void Slots::toggleEnd(){
    end = !end;
    if(end) setGreen();
    else setWhite();
}
