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
            throw std::runtime_error("Syntax error: unexpected token in stream: \""
                                     + currToken.value + "\"");
        }
    }
    else {
        if(currToken.type != type || currToken.value != value) {
            throw std::runtime_error("Syntax error: unexpected token in stream: \""
                                     + currToken.value);
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
    //expect(TokenType::Op, ".");
}

/* block = [ "const" ident "=" number {"," ident "=" number} ";"]
        [ "var" ident {"," ident} ";"]
        { "procedure" ident ";" block ";" } statement ; */
void Parser::block() {
    /* [ "const" ident "=" number {"," ident "=" number} ";"] */
    if(check(TokenType::Keyword, "const")) {
        std::cout << currToken.value << std::endl;
        nextToken();
        expect(TokenType::Ident);
        expect(TokenType::Op, "=");
        expect(TokenType::Num);
        while(check(TokenType::Op, ",")) {
            std::cout << currToken.value << std::endl;
            nextToken();
            expect(TokenType::Ident);
            expect(TokenType::Op, "=");
            expect(TokenType::Num);
        }
        expect(TokenType::Op, ";");
    }

    /* [ "var" ident {"," ident} ";"] */
    if(check(TokenType::Keyword, "var")) {
        std::cout << currToken.value << std::endl;
        nextToken();
        expect(TokenType::Ident);
        while(check(TokenType::Op, ",")) {
            std::cout << currToken.value << std::endl;
            nextToken();
            expect(TokenType::Ident);
        }
        expect(TokenType::Op, ";");
    }

    /* { "procedure" ident ";" block ";" } statement ; */
    while(check(TokenType::Keyword, "procedure")) {
        std::cout << currToken.value << std::endl;
        nextToken();
        expect(TokenType::Ident);
        expect(TokenType::Op, ";");
        block();
    }

    statement();
    //TODO don't forget to uncomment after statement() is written
    //expect(TokenType::Op, ";");
}

/* statement = [ ident ":=" expression | "call" ident
              | "?" ident | "!" expression
              | "begin" statement {";" statement } "end"
              | "if" condition "then" statement
              | "while" condition "do" statement ]; */
void Parser::statement() {
    if(check(TokenType::Ident)) {
        //TODO
    }
}

void Parser::condition() {

}

void Parser::expression() {

}

void Parser::term() {

}

void Parser::factor() {

}
