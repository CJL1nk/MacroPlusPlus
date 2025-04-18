//
// Created by CJ on 4/16/2025.
//

#include "input.h"

void sendKey(KeySym key, KeyState state) {

    KeyCode keycode = XKeysymToKeycode(display, key);
    XTestFakeKeyEvent(display, keycode, (state == KeyState::DOWN) ? True : False, 0);
}

void sleep(int ms) {
    usleep(ms * 1000); // usleep is in microseconds
}

bool setMousePos(int x, int y) {
    std::cout << "Set Mouse Pos: " << x << ", " << y << std::endl;
    return true;
}
