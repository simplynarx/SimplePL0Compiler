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

        void nextToken();
        void expect(TokenType type, std::string value);
        bool check(TokenType type, std::string value);

        void program();
        void block();
        void statement();
        void condition();
        void expression();
        void term();
        void factor();
};
