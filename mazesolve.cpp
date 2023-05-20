#include "mazesolve.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QString>

#include <fstream>
#include <utility>
#include <set>
#include <queue>

#define PI std::pair<int, int>
#define SII std::set<PI>

bool helper(PI start, SII&end, VSS&arr, const int&h, const int&w);

bool MazeSolve::saveArr(const std::string&dir, const VSS&dat){
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

VSS MazeSolve::loadArr(const std::string&dir){
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

bool MazeSolve::solve(int h, int w, VSS&arr) {
    PI start;
    SII end;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (arr[i][j] == "S")
                start = {i, j};
            else if (arr[i][j] == "E")
                end.insert({i, j});
        }
    }
    return helper(start, end, arr, h, w);
}

bool helper(PI start, SII&end, VSS&arr, const int&h, const int&w) {
    std::queue<PI> q;
    std::vector<std::vector<PI>> parent(h, std::vector<PI>(w, {-1, -1}));
    q.push(start);
    parent[start.first][start.second] = {-2, -2};

    while (!q.empty()) {
        PI curr = q.front();
        q.pop();

        if (end.count(curr) == 1) {
            PI pathNode = curr;
            while (parent[pathNode.first][pathNode.second].first != -2 || parent[pathNode.first][pathNode.second].second != -2){
                PI prev = parent[pathNode.first][pathNode.second];
                arr[pathNode.first][pathNode.second] = "T";
                pathNode = prev;
            }
            arr[start.first][start.second] = "T";
            return true;
        }

        int i = curr.first, j = curr.second;
        if (i >= h || i < 0 || j >= w || j < 0 || arr[i][j] == "P" || arr[i][j] == "W")
            continue;

        arr[i][j] = "P";
        if (i - 1 >= 0 && arr[i - 1][j] != "P" && arr[i - 1][j] != "W") {
            q.push({i - 1, j});
            parent[i - 1][j] = {i, j};
        }
        if (i + 1 < h && arr[i + 1][j] != "P" && arr[i + 1][j] != "W") {
            q.push({i + 1, j});
            parent[i + 1][j] = {i, j};
        }
        if (j - 1 >= 0 && arr[i][j - 1] != "P" && arr[i][j - 1] != "W") {
            q.push({i, j - 1});
            parent[i][j - 1] = {i, j};
        }
        if (j + 1 < w && arr[i][j + 1] != "P" && arr[i][j + 1] != "W") {
            q.push({i, j + 1});
            parent[i][j + 1] = {i, j};
        }
    }
    return false;
}

