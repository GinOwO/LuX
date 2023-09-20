#include <vector>
#include <string>

#ifndef MAZESOLVE_H
#define MAZESOLVE_H

#define VS std::vector<std::string>
#define VSS std::vector<VS>


class MazeSolve{
public:
    static bool saveArr(const std::string& dir, const VSS&dat);
    static VSS loadArr(const std::string& dir);
    static std::string getDir();
    static bool solve(int h, int w, VSS&arr);
};

#endif // MAZESOLVE_H
