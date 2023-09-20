#include "mazesolve.h"

#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QDir>

#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <stack>

bool bfs(PI start, SII&end, VSS&arr, const int&h, const int&w);
bool dfs(PI start, SII&end, VSS&arr, const int&h, const int&w);
bool floodFill(PI start, SII&end, VSS&arr, const int&h, const int&w);

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
    QString location = QFileDialog::getOpenFileName(nullptr,"Load Maze",QDir::currentPath(), "Text files(*.txt) || All Files(*)");
    if (location.isEmpty()) {
        QMessageBox::critical(nullptr, "Error", "No Path Entered");
        return "";
    }
    return location.toStdString();
}

bool MazeSolve::solve(int h, int w, VSS&arr, int id) {
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
    if(id==0) return dfs(start, end, arr, h, w);
    else if(id==1) return bfs(start, end, arr, h, w);
    else if(id==2) return floodFill(start, end, arr, h, w);
    return false;
}

bool bfs(PI start, SII&end, VSS&arr, const int&h, const int&w) {
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

bool dfs(PI start, SII&end, VSS&arr, const int&h, const int&w){
    if(end.count(start)==1) return true;

    int i = start.first, j = start.second;
    if(i >= h || i < 0 || j >= w || j < 0
        || arr[i][j]=="P"||arr[i][j]=="W") return false;
    arr[i][j] = "P";

    if( dfs({i,j+1},end,arr,h,w) || dfs({i,j-1},end,arr,h,w)||
            dfs({i+1,j},end,arr,h,w) || dfs({i-1,j},end,arr,h,w)){
        arr[i][j] = "T";
        return true;
    }
    else return false;
}

bool floodFill(PI start, SII& end, VSS& arr, const int& h, const int& w) {
    std::queue<PI> q;
    std::vector<std::vector<bool>> visited(h, std::vector<bool>(w, false));
    std::vector<std::vector<PI>> parent(h, std::vector<PI>(w, {-1, -1}));

    q.push(start);
    visited[start.first][start.second] = true;

    while (!q.empty()) {
        PI curr = q.front();
        q.pop();

        if (end.count(curr) == 1) {
            PI pathNode = curr;
            while (pathNode != start) {
                arr[pathNode.first][pathNode.second] = "T";
                pathNode = parent[pathNode.first][pathNode.second];
            }
            arr[start.first][start.second] = "T";
            return true;
        }

        int i = curr.first, j = curr.second;
        const std::vector<PI> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (const auto& dir : directions) {
            int new_i = i + dir.first;
            int new_j = j + dir.second;

            if (new_i >= 0 && new_i < h && new_j >= 0 && new_j < w &&
                !visited[new_i][new_j] && arr[new_i][new_j] != "W") {
                q.push({new_i, new_j});
                visited[new_i][new_j] = true;
                parent[new_i][new_j] = curr;
            }
        }
    }

    return false;
}
