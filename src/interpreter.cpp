//
// Created by CJ on 4/16/2025.
//

#include "interpreter.h"

bool start(std::istream& infile) {

    std::string currLine;
    std::string instruction;
    std::string arg;
    std::pair<size_t, size_t> captureBracketPos;

    // Map mapping each instruction to a lambda function dealing with their high level logic
    // The devious map of string to lambda function:
    const std::unordered_map<std::string, std::function<void(const std::string&)>> instructionMap = {
        {"Key", [](const std::string& arg) { sendChar(arg[0]); }},
        {"Mod", [](const std::string& arg) { sendModifier(getModFromStr(arg)); }},
        {"Sleep", [](const std::string& arg) { sleep(std::stoi(arg)); }},
        {"Mouse", [](const std::string& arg) { sendMouse(getMouseFromStr(arg)); }},
        {"LOOP", [&infile](const std::string& arg) {
            size_t commaPos = arg.find_first_of(',');
            std::string label = arg.substr(1, commaPos - 1); // Get label
            size_t count = std::stoi(arg.substr(commaPos + 1)) - 1; // Get loop count, - 1 to account for initial pass
            loops[label] = Loop(infile.tellg(), count); // Save to loop dict
            }},
        {"GOTO", [&infile](const std::string& arg) {
            std::string label = arg.substr(1); // Get label
            Loop& loop = loops.at(label); // Get loop object
            if (loop.count > 0) { // Loop until no loops left
                loop.count--;
                infile.seekg(loop.line); // Seek back to original line
            }
        }}
    };

    while (infile.good()) {
        // While next line exists

        std::getline(infile, currLine); // Get next line
        currLine.erase(std::remove(currLine.begin(), currLine.end(), '\r'), currLine.end());

        if (currLine[0] == '#' || currLine.empty()) { continue; } // Go on to next line if comment or empty

        captureBracketPos = getCaptureBracketPos(currLine); // Get capture bracket positions
        instruction = getInstruction(currLine, captureBracketPos.first); // Get instruction from line
        arg = getArg(currLine, captureBracketPos); // Get argument from line

        try { // Call function at instruction map with arg
            instructionMap.at(instruction)(arg);
        } catch (std::out_of_range& e) { // If instruction didn't exist
            throw std::runtime_error("Invalid Instruction");
        } catch (std::exception& e) { // If some random bullshit happened
            throw std::runtime_error(e.what());
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

MouseBtn getMouseFromStr(std::string btnStr) {
    return mouseBtns[btnStr];
}