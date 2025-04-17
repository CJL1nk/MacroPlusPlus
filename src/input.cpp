//
// Created by CJ on 4/16/2025.
//

#include "input.h"

void sendModifier(Modifier mod) {
    std::cout << "Sent Modifier: " << mod << std::endl;
}

void sendChar(char c) {
    std::cout << "Sent Char: " << c << std::endl;
}

void sendMouse(MouseBtn btn) {
    std::cout << "Sent MouseBtn: " << btn << std::endl;
}

void sleep(int ms) {
    usleep(ms * 1000); // usleep is in microseconds
}

bool setMousePos(int x, int y) {
    return false;
}
