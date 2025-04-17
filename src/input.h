//
// Created by CJ on 4/16/2025.
//

#ifndef INPUT_H
#define INPUT_H

enum Modifier;
enum MouseBtn;

void sendModifier(Modifier mod);
void sendChar(char c);
void sendMouse(MouseBtn m);

#endif //INPUT_H
