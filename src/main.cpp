#include <lexer.hpp>
#include <parser.hpp>

#include <iostream>
#include <vector>

int main(int argc, char **argv) {
    if (argc !=  2) {
        std::cerr << "usage: ./SimplePL0Compiler <filename>.pl0\n" << std::endl;
        return 1;
    }

   /* Lexing process */

   Lexer lexer(argv[1]);

   std::vector<Token> tokens = lexer.tokenize();
   lexer.print_tokens(tokens);


   return 0;
}

