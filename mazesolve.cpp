#include "mazesolve.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QString>

#include <fstream>
#include <utility>
#include <set>
#include <stack>

#define PI std::pair<int, int>
#define SII std::set<PI>

bool helper(PI start, SII&end, VSS&arr, const int&h, const int&w);

bool MazeSolve::saveArr(const std::string& dir, const VSS&dat){
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
    if (location.isEmpty()) {
        QMessageBox::critical(nullptr, "Error", "No Path Entered");
        return "";
    }
    return location.toStdString();
}

bool MazeSolve::solve(int h, int w, VSS&arr){
    PI start; SII end;
    for(int i=0;i<h;i++) for(int j=0;j<w;j++){
            if (arr[i][j]=="S") start.first=i,start.second=j;
            if (arr[i][j]=="E") end.insert({i,j});
        }
    return helper(start, end, arr, h, w);
}


bool helper(PI start, SII&end, VSS&arr, const int&h, const int&w){
    if(end.count(start)==1) return true;

    int i = start.first, j = start.second;
    if(i >= h || i < 0 || j >= w || j < 0
        || arr[i][j]=="P"||arr[i][j]=="W") return false;
    arr[i][j] = "P";

    if( helper({i,j+1},end,arr,h,w) || helper({i,j-1},end,arr,h,w)||
        helper({i+1,j},end,arr,h,w) || helper({i-1,j},end,arr,h,w)){
        arr[i][j] = "T";
        return true;
    }
    else return false;
}
