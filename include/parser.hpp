#pragma once

#include <lexer.hpp>

#include <stdexcept>

class Parser {
    public:
        Parser(Lexer &lexer);
        void parse();

    private:
        Lexer &lexer;
        Token currToken;
        bool debug_toggle;
        std::string tree_pos;

        void nextToken();
        void expect(TokenType type, std::string value);
        bool check(TokenType type, std::string value);
        void debug();

        void program();
        void block();
        void statement();
        void condition();
        void expression();
        void term();
        void factor();
};
