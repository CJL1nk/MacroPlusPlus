//
// Created by CJ on 4/16/2025.
//

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <fstream>
#include <utility>
#include <functional>

#include "input.h"

struct Loop {
    std::streampos line;
    size_t count;
};

inline std::unordered_map<std::string, Loop> loops;
inline std::unordered_map<std::string, Modifier> mods
{   {"LCTRLDOWN", LCTRLDOWN},
    {"LCTRLUP", LCTRLUP},
    {"LSHIFTDOWN", LSHIFTDOWN},
    {"LSHIFTUP", LSHIFTUP},
    {"LALTDOWN", LALTDOWN},
    {"LALTUP", LALTUP},
    {"RCTRLDOWN", RCTRLDOWN},
    {"RCTRLUP", RCTRLUP},
    {"RSHIFTDOWN", RSHIFTDOWN},
    {"RSHIFTUP", RSHIFTUP},
    {"RALTDOWN", RALTDOWN},
    {"RALTUP", RALTUP},
    {"WINDOWN", WINDOWN},
    {"WINUP", WINUP}
};
inline std::unordered_map<std::string, MouseBtn> mouseBtns
{
    {"LDOWN", LDOWN},
    {"LUP", LUP},
    {"MDOWN", MDOWN},
    {"MUP", MUP},
    {"RDOWN", RDOWN},
    {"RUP", RUP},
    {"WHEELDOWN", WHEELDOWN},
    {"WHEELUP", WHEELUP}
};

bool start(std::istream& infile);
bool exec(std::string instruction, std::string arg);
std::string getInstruction(std::string line, size_t& captureBracketPos);
std::pair<size_t, size_t> getCaptureBracketPos(std::string line);
std::string getArg(std::string line, std::pair<size_t, size_t> captureBracketPos);
Modifier getModFromStr(std::string modStr);
MouseBtn getMouseFromStr(std::string btnStr);

#endif //INTERPRETER_H
