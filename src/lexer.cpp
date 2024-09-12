#include "lexer.h"

char *data;
std::vector<char> lexeme;

/**
 * error - template function to display error messages
 *
 * args:
 * err - an error message
 */
void error(std::string err) {
    std::cerr << "error: " << err << std::endl;
}

/**
 * read_file - read in file for lexing and parsing
 *
 * args:
 * fname - input file name (taken from argv)
 */
void read_file(std::string fname) {
    //Check filename for appropriate extension
    if(fname.find('.') == std::string::npos) {
        error("file must end in .pl0");
        exit(1);
    }

    if(fname.find(".pl0") == std::string::npos) {
        error("file must end in .pl0");
        exit(1);
    }

    //Open file
    std::ifstream fp(fname, std::ios::ate | std::ios::binary);

    //Check file for errors
    if(!fp) {
        error("file could not be opened");
        exit(1);
    }

    auto size = fp.tellg();
    fp.seekg(0, std::ios::beg);

    if(size == 0) { error("file is empty"); }

    data = new char[size];

    if(!fp.read(data, size)) {
        error("could not read file");
    }
}

/* LEXER FUNCTIONS */
