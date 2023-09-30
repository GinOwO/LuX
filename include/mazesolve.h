#ifndef MAZESOLVE_H
#define MAZESOLVE_H

#include <QString>

#include <vector>
#include <string>
#include <set>

#define PI std::pair<int, int>
#define SII std::set<PI>
#define VS std::vector<std::string>
#define VSS std::vector<VS>

class MazeSolve{
public:
    static bool saveArr(const QString& dir, const VSS&dat);
    static VSS loadArr(const QString& dir);
    static QString getDir();
    static bool solve(int h, int w, VSS&arr, int);
};

#endif // MAZESOLVE_H
