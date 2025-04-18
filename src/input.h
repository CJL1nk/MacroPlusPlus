//
// Created by CJ on 4/16/2025.
//

#ifndef INPUT_H
#define INPUT_H

#include <unistd.h>
#include <iostream>

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>

inline Display* display;

enum KeyState {
    UP,
    DOWN
};

void sendKey(KeySym key, KeyState state);
void sleep(int ms);
bool setMousePos(int x, int y);

#endif //INPUT_H
