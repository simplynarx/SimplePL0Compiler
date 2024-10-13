#include <lexer.hpp>
#include <parser.hpp>

#include <iostream>
#include <stdexcept>

int main(int argc, char **argv) {
    if (argc !=  2) {
        std::cerr << "usage: ./SimplePL0Compiler <filename>.pl0\n" << std::endl;
        return 1;
    }

   Lexer lexer(argv[1]);
   Parser parser(lexer);

   try {
       parser.parse();
   }
   catch(const std::runtime_error &e) {
       std::cerr << e.what() << std::endl;
   }

   //std::vector<Token> tokens = lexer.tokenize();
   //lexer.print_tokens(tokens);


   return 0;
}

