#include <fstream>
#include <vector>
#include <string>

#ifndef MAZESOLVE_H
#define MAZESOLVE_H

#define VS std::vector<std::string>
#define VSS std::vector<VS>


class MazeSolve{
public:
    static bool saveArr(const VSS&dat, const std::string& dir);
    static VSS loadArr(const std::string& dir);
    static std::string getDir();
};

#endif // MAZESOLVE_H
