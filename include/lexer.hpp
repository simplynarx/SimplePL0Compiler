#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cctype>
#include <algorithm>
#include <iomanip>

enum class TokenType { Ident, Num, Keyword, Op, EndOfFile, Invalid };

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
    public:
        Lexer(const std::vector<char> &src);
        Token get_next_token();
        std::vector<Token> tokenize();
        void print_tokens(const std::vector<Token> &tokens);

    private:
        std::vector<char> input;
        size_t pos;
        char peek();
        char get_next_char();
        bool is_keyword(const std::string &word);
};
