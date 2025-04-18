#include <iostream>

#include "main.h"

int main(int arc, char* argv[]) {

    std::ifstream infile("../macros/macro1.macl", std::ios::binary);

    start(infile);

    return 0;
}