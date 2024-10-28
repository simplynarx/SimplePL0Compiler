#pragma once

#include <lexer.hpp>
#include <transpiler.hpp>

#include <stdexcept>

class Parser {
    public:
        Parser(Lexer &lexer, Transpiler &transpiler);
        void parse();

    private:
        Lexer &lexer;
        Transpiler &transpiler;
        Token curr_token;
        std::string curr_keyword;
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
