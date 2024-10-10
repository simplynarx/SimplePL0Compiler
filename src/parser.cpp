#include "lexer.hpp"
#include <parser.hpp>

Parser::Parser(Lexer &lexer) : lexer(lexer) {
    nextToken();
}

void Parser::parse() {
    program();
}

/**
 * nextToken - retrieves the next token from the lexer
 */
void Parser::nextToken() {
    currToken = lexer.get_next_token();
}

/**
 * expect - ensures the current TokenType matches
 * the expected TokenType
 *
 * args:
 * type - another TokenType
 *
 * throws:
 * runtime_error - if the current token does not match the
 * expected token
 */
void Parser::expect(TokenType type, std::string value = "") {
    if(value.empty()) {
        if(currToken.type != type) {
            throw std::runtime_error("Syntax error: unexpected token in stream");
        }
    }
    else {
        if(currToken.type != type || currToken.value != value) {
            throw std::runtime_error("Syntax error: unexpected token in stream");
        }
    }
    std::cout << currToken.value << std::endl;
    nextToken();
}

/**
 * checks - checks, but does not ensure, that the current
 * TokenType matches the expected TokenType
 *
 */
bool Parser::check(TokenType type, std::string value = "") {
    if(value.empty()) {
        return currToken.type == type ? true : false;
    }
    else {
        return currToken.value == value ? true : false;
    }
}

/* program = block "." ; */
void Parser::program() {
    block();
    expect(TokenType::Op, ".");
}

//TODO
/* block = [ "const" ident "=" number {"," ident "=" number} ";"]
        [ "var" ident {"," ident} ";"]
        { "procedure" ident ";" block ";" } statement ; */
void Parser::block() {
    if(check(TokenType::Keyword, "const")) {
        std::cout << currToken.value << std::endl;
        nextToken();
        expect(TokenType::Ident);
        expect(TokenType::Op, "=");
        expect(TokenType::Num);
        while(check(TokenType::Op, ",")) {
            expect(TokenType::Ident);
            expect(TokenType::Op, "=");
            expect(TokenType::Num);
        }
        expect(TokenType::Op, ";");
    }
}

void Parser::statement() {

}

void Parser::condition() {

}

void Parser::expression() {

}

void Parser::term() {

}

void Parser::factor() {

}
