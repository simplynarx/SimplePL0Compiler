#include <lexer.hpp>

Lexer::Lexer(const std::vector<char> &src) {
    input = src;
    pos = 0;
}

char Lexer::peek() {
    return (pos < input.size() ? input.at(pos) : '\0');
}

char Lexer::getNextChar() {
    return (pos < input.size() ? input.at(pos++) : '\0');
}

bool Lexer::isKeyword(const std::string &word) {
    return keywords.find(word) != keywords.end();
}

Token Lexer::getNextToken() {
    while(std::isspace(peek())) {
        getNextChar();
    }

    char currChar = peek();

    if(currChar == '\0') {
        return (TokenType::EndOfFile, "");
    }
}
