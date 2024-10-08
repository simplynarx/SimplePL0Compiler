#include <lexer.hpp>

#include <iostream>
#include <fstream>
#include <vector>

std::vector<char> src;

/**
 * read_file - read in file for lexing and parsing
 *
 * args:
 * fname - input file name (taken from argv)
 */
static void read_file(std::string fname) {
    //Check filename for appropriate extension
    if(fname.find('.') == std::string::npos) {
        std::cerr << "error: file must end in .pl0" << std::endl;
        exit(1);
    }

    if(fname.find(".pl0") == std::string::npos) {
        std::cerr << "error: file must end in .pl0" << std::endl;
        exit(1);
    }

    //Open file, starting on the last character
    std::ifstream fp(fname, std::ios::ate | std::ios::binary);

    //Check file for errors
    if(!fp) {
        std::cerr << "error: file could not be opened" << std::endl;
        exit(1);
    }

    auto size = fp.tellg();
    fp.seekg(0, std::ios::beg);

    if(size == 0) {
        std::cerr << "error: file is empty" << std::endl;
        exit(1);
    }

    src.resize(size);

    if(!fp.read(src.data(), size)) {
        std::cerr << "error: could not read file" << std::endl;
    }

    fp.close();

}

int main(int argc, char **argv) {
    if (argc !=  2) {
        std::cerr << "usage: ./SimplePL0Compiler <filename>.pl0\n" << std::endl;
        return 1;
    }

   read_file(argv[1]);

   /* Lexing process */

   Lexer lex(src);

   std::vector<Token> tokens = lex.tokenize();
   lex.print_tokens(tokens);


   return 0;
}

