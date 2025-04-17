//
// Created by CJ on 4/16/2025.
//

#ifndef INPUT_H
#define INPUT_H

#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <iostream>

enum Modifier {
    LCTRLDOWN,
    LCTRLUP,
    LSHIFTDOWN,
    LSHIFTUP,
    LALTDOWN,
    LALTUP,
    RCTRLDOWN,
    RCTRLUP,
    RSHIFTDOWN,
    RSHIFTUP,
    RALTDOWN,
    RALTUP,
    WINDOWN,
    WINUP
};;
enum MouseBtn {
    LDOWN,
    LUP,
    MDOWN,
    MUP,
    RDOWN,
    RUP,
    WHEELUP,
    WHEELDOWN,
};

void sendModifier(Modifier mod);
void sendChar(char c);
void sendMouse(MouseBtn m);
void sleep(int ms);
bool setMousePos(int x, int y);

#endif //INPUT_H
