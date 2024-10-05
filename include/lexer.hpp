#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <cctype>

enum class TokenType { Ident, Num, Keyword, Op, EndOfFile, Invalid };

struct Token {
    TokenType type;
    std::string value;
};

std::unordered_map<std::string, TokenType> keywords = {
{"begin", TokenType::Keyword},
{"end", TokenType::Keyword},
{"if", TokenType::Keyword},
{"then", TokenType::Keyword},
{"while", TokenType::Keyword},
{"do", TokenType::Keyword},
{"const", TokenType::Keyword},
{"var", TokenType::Keyword},
{"procedure", TokenType::Keyword},
{"odd", TokenType::Keyword},
{"call", TokenType::Keyword},
};

class Lexer {
    public:
        Lexer(const std::vector<char> &src);
        Token getNextToken();
        std::vector<Token> tokenize();

    private:
        std::vector<char> input;
        size_t pos;
        char peek();
        char getNextChar();
        bool isKeyword(const std::string &word);
};
