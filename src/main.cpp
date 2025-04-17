#include <iostream>

#include "main.h"

int main(int arc, char* argv[]) {

    std::ifstream infile("../macros/macro1.macl");

    start(infile);

    return 0;
}