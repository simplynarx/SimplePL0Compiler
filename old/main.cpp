#include <iostream>

#include "lexer.h"

int main(int argc, char **argv) {
    if(argc != 2) {
        std::cerr << "error: usage: SimplePL0Compiler file.pl0\n" << std::endl;
        exit(1);
    }

    read_file(argv[1]);

    return 0;
}
