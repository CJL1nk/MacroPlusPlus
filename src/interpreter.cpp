//
// Created by CJ on 4/16/2025.
//

#include "interpreter.h"

/**
 * Main loop of the program, creates a map containing logic for each instruction
 * @param infile Input file to read from
 * @return true if finished successfully, will error otherwise
 */
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
        {"Modifier", [](const std::string& arg) { sendModifier(getModFromStr(arg)); }},
        {"Sleep", [](const std::string& arg) { sleep(std::stoi(arg)); }},
        {"Mouse", [](const std::string& arg) { sendMouse(getMouseFromStr(arg)); }},

        {"MousePos", [](const std::string& arg) {
            std::pair<int, int> pos = getMousePosFromArg(arg);
            setMousePos(pos.first, pos.second);
        }},

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

    while (infile.good()) { // While next line exists

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

/**
 * Grabs and returns the instruction from a given line
 * @param line Line to read from
 * @param captureBracketPos Position of the first capture bracket, terminator for reading
 * @return String containing the raw instruction
 */
std::string getInstruction(std::string line, size_t& captureBracketPos) {
    return line.substr(0, captureBracketPos); // Get instruction from line
}

/**
 * Gets the positions of the capture brackets in a program, OR a : in the case of a LOOP or GOTO
 * @param line Line to read from
 * @return Positions of given line's capture brackets
 */
std::pair<size_t, size_t> getCaptureBracketPos(std::string line) {
    return std::pair<size_t, size_t>(line.find_first_of("[:"), line.find_first_of(']'));
}

/**
 * Gets the argument within the capture brackets OR the argument after : in the case of a LOOP or GOTO
 * @param line Line to read from
 * @param captureBracketPos Positions of capture brackets
 * @return Argument of given line
 */
std::string getArg(std::string line, std::pair<size_t, size_t> captureBracketPos) {
    return line.substr(captureBracketPos.first + 1, captureBracketPos.second - captureBracketPos.first - 1);
}

/**
 * Grabs and returns an enumerated version of a modifier
 * @param modStr Name of modifier
 * @return Enumeration of modifier
 */
Modifier getModFromStr(std::string modStr) {
    return mods[modStr];
}

/**
 * Grabs and returns an enumerated version of a mouse button
 * @param btnStr Name of mouse button
 * @return Enumeration of mouseButton
 */
MouseBtn getMouseFromStr(std::string btnStr) {
    return mouseBtns[btnStr];
}

/**
 * Gets and returns a pair containing the X and Y positions of a mouse position argument
 * @param posStr Argument containing mouse positions
 * @return Pair of ints containing X and Y of given mouse position argument
 */
std::pair<int, int> getMousePosFromArg(std::string posStr) {

    std::pair<int, int> pos;
    size_t commaPos = posStr.find(',');

    pos.first = std::stoi(posStr.substr(0, commaPos));
    pos.second = std::stoi(posStr.substr(commaPos + 1));

    return pos;
}