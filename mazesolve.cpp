#include "mazesolve.h"
#include <QString>
#include <QMessageBox>
#include <QInputDialog>

bool MazeSolve::saveArr(const VSS&dat, const std::string& dir){
    std::ofstream handle(dir);
    if(handle.fail()){
        handle.close();
        return false;
    }
    handle << dat.size() << ' ' << dat[0].size() <<'\n';
    for(auto&i:dat){
        for(auto&c:i) handle << c << ' ';
        handle << '\n';
    }
    handle.close();
    return true;
}


VSS MazeSolve::loadArr(const std::string& dir){
    std::ifstream handle(dir);
    if(handle.fail()){
        handle.close();
        return {};
    }
    int h,w; handle >> h >> w;
    VSS arr(h);
    for(int i=0;i<h;i++){
        arr[i] = VS(w);
        for(int j=0;j<w;j++){
            handle >> arr[i][j];
        }
    }
    return arr;
}

std::string MazeSolve::getDir(){
    QString location = QInputDialog::getText(nullptr, "Enter Location", "Location:");
    if (!location.isEmpty()) {
        QMessageBox::critical(nullptr, "Error", "No Path Entered");
        return "";
    }
    return location.toStdString();
}
