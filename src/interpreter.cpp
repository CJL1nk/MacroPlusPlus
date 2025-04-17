//
// Created by CJ on 4/16/2025.
//

#include "interpreter.h"

#include <algorithm>


bool start(std::istream& infile) {

    std::string currLine;
    std::string instruction;
    std::string arg;
    std::pair<size_t, size_t> captureBracketPos;

    const std::map<std::string, std::function<void(const std::string&)>> instructionMap = {
        {"Key", [](const std::string& arg) { sendChar(arg[0]); }},
        {"Mod", [](const std::string& arg) { sendModifier(getModFromStr(arg)); }},
        {"Sleep", [](const std::string& arg) { sleep(std::stoi(arg)); }},
        {"MouseBtn", [](const std::string& arg) { /* handle mouse button */ }},
        {"LOOP", [](const std::string& arg) { std::cout << "LOOP" << std::endl; }},
        {"GOTO", [](const std::string& arg) { std::cout << "GOTO" << std::endl; }}
    };


    std::cout << "Playback Started" << std::endl;

    while (infile.good()) {

        std::getline(infile, currLine); // Get next line
        if (currLine.starts_with('#') || currLine.empty()) { continue; } // Go on to next line if comment or empty

        captureBracketPos = getCaptureBracketPos(currLine); // Get capture bracket positions
        instruction = getInstruction(currLine, captureBracketPos.first); // Get instruction from line
        arg = getArg(currLine, captureBracketPos); // Get argument from line

        if (auto it = instructionMap.find(instruction); it != instructionMap.end()) {
            it->second(arg);
        } else {
            throw std::runtime_error("Invalid Instruction");
        }

    }

    return true;
}

std::string getInstruction(std::string line, size_t& captureBracketPos) {
    return line.substr(0, captureBracketPos); // Get instruction from line
}

std::pair<size_t, size_t> getCaptureBracketPos(std::string line) {
    return std::pair<size_t, size_t>(line.find_first_of("[:"), line.find_first_of(']'));
}

std::string getArg(std::string line, std::pair<size_t, size_t> captureBracketPos) {
    return line.substr(captureBracketPos.first + 1, captureBracketPos.second - captureBracketPos.first - 1);
}

Modifier getModFromStr(std::string modStr) {
    return mods[modStr];
}