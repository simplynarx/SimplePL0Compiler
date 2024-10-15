#include <parser.hpp>

Parser::Parser(Lexer &lexer, Transpiler &transpiler) : lexer(lexer), transpiler(transpiler) {
    nextToken();
    debug_toggle = false;
}

/**
 * parse - parses the token stream
 */
void Parser::parse() {
    program();
}

/**
 * nextToken - retrieves the next token from the lexer
 */
void Parser::nextToken() {
    curr_token = lexer.get_next_token();
}

/**
 * expect - ensures the current TokenType matches
 * the expected TokenType
 *
 * args:
 * type - another TokenType
 * value - optional string for an exact value match
 *
 * throws:
 * runtime_error - if the current token does not match the
 * expected token
 */
void Parser::expect(TokenType type, std::string value = "") {
    // if only a token type is passed
    if(value.empty()) {
        if(curr_token.type != type) {
            throw std::runtime_error("Syntax error: unexpected token in stream: \""
                                     + curr_token.value + "\"");
        }
    }
    else {
        if(curr_token.type != type || curr_token.value != value) {
            throw std::runtime_error("Syntax error: unexpected token in stream: \""
                                     + curr_token.value);
        }
    }
    debug();
    nextToken();
}

/**
 * check - checks, but does not ensure, that the current
 * TokenType matches the expected TokenType
 *
 * returns:
 * true if equal, false otherwise
 */
bool Parser::check(TokenType type, std::string value = "") {
    // if only a token type is passed
    if(value.empty()) {
        return curr_token.type == type ? true : false;
    }
    else {
        return curr_token.value == value ? true : false;
    }
}

/**
 * debug - displays the value of a token and its position in the
 * parse tree. enabled by setting debug_toggle to true in constructor
 */
void Parser::debug() {
    if(debug_toggle) {
        std::cout << "Parse Tree: " << tree_pos
                  << "\tValue: " << curr_token.value << std::endl;
    }
}

/* program = block "." ; */
void Parser::program() {
    tree_pos = "<program>";
    debug();

    block();
    expect(TokenType::Op, ".");
}

/* block = [ "const" ident "=" number {"," ident "=" number} ";"]
        [ "var" ident {"," ident} ";"]
        { "procedure" ident ";" block ";" } statement ; */
void Parser::block() {
    tree_pos = "<block>";

    /* [ "const" ident "=" number {"," ident "=" number} ";"] */
    if(check(TokenType::Keyword, "const")) {
        debug();
        nextToken();

        transpiler.t_const(curr_token.value);

        expect(TokenType::Ident);
        expect(TokenType::Op, "=");

        transpiler.t_num(curr_token.value);

        expect(TokenType::Num);
        while(check(TokenType::Op, ",")) {
            transpiler.t_comma();

            debug();
            nextToken();

            transpiler.t_const_assignment(curr_token.value);

            expect(TokenType::Ident);
            expect(TokenType::Op, "=");

            transpiler.t_num(curr_token.value);

            expect(TokenType::Num);
        }

        transpiler.t_semicolon();

        expect(TokenType::Op, ";");
    }

    /* [ "var" ident {"," ident} ";"] */
    if(check(TokenType::Keyword, "var")) {
        debug();
        nextToken();

        transpiler.t_var(curr_token.value);

        expect(TokenType::Ident);
        while(check(TokenType::Op, ",")) {
            transpiler.t_comma();

            debug();
            nextToken();

            transpiler.t_ident(curr_token.value);

            expect(TokenType::Ident);
        }

        transpiler.t_semicolon();

        expect(TokenType::Op, ";");
    }

    /* { "procedure" ident ";" block ";" } statement ; */
    while(check(TokenType::Keyword, "procedure")) {
        debug();
        nextToken();

        transpiler.t_procedure(curr_token.value);

        expect(TokenType::Ident);
        expect(TokenType::Op, ";");
        block();
        expect(TokenType::Op, ";");
    }

    statement();
}

/* statement = [ ident ":=" expression | "call" ident
              | "?" ident | "!" expression
              | "begin" statement {";" statement } "end"
              | "if" condition "then" statement
              | "while" condition "do" statement ]; */
void Parser::statement() {
    tree_pos = "<statement>";

    /* ident ":=" expression */
    if(check(TokenType::Ident)) {
        debug();

        transpiler.t_var_assignment(curr_token.value);

        nextToken();
        expect(TokenType::Op, ":=");
        expression();
    }

    // TODO implement keyword tracker to determine when
    // main should be created. if last keyword was "end"
    // when either "begin" or "call" are parsed, create main

    /* "call" ident */
    if(check(TokenType::Keyword, "call")) {
        debug();
        nextToken();

        transpiler.t_call(curr_token.value);

        expect(TokenType::Ident);
    }

    /* "?" ident */
    if(check(TokenType::Op, "?")) {
        debug();
        nextToken();

        transpiler.t_input(curr_token.value);

        expect(TokenType::Ident);
    }

    /* "!" ident */
    if(check(TokenType::Op, "!")) {
        debug();
        nextToken();

        transpiler.t_output(curr_token.value);

        expression();
    }

    /* "begin" statement {";" statement} "end" */
    if(check(TokenType::Keyword, "begin")) {
        debug();
        nextToken();
        statement();
        while(check(TokenType::Op, ";")) {
            debug();

            transpiler.t_semicolon();

            nextToken();
            statement();
        }

        transpiler.t_end();

        expect(TokenType::Keyword, "end");
    }

    /* "if" condition "then" statement */
    if(check(TokenType::Keyword, "if")) {
        debug();
        nextToken();
        condition();
        expect(TokenType::Keyword, "then");
        statement();
    }

    /* "while" condition "do" statement */
    if(check(TokenType::Keyword, "while")) {
        debug();
        nextToken();
        condition();
        expect(TokenType::Keyword, "do");
        statement();
    }
}

/* condition = "odd" expression |
            expression ("="|"#"|"<"|"<="|">"|">=") expression ; */
void Parser::condition() {
    tree_pos = "<condition>";

    /* "odd" expression */
    if(check(TokenType::Keyword, "odd")) {
        debug();
        nextToken();
        expression();
    }
    else {
        /* expression ("="|"#"|"<"|"<="|">"|">=") expression ; */
        expression();
        if (check(TokenType::Op, "=") || check(TokenType::Op, "#") ||
            check(TokenType::Op, "<") || check(TokenType::Op, "<=") ||
            check(TokenType::Op, ">") || check(TokenType::Op, ">=")) {
        debug();
        nextToken();
        expression();
        }
        else throw std::runtime_error("Syntax error: unexpected token in stream: \""
                                     + curr_token.value + "\"");
    }

}

/* expression = [ "+"|"-"] term { ("+"|"-") term}; */
void Parser::expression() {
    tree_pos = "<expression>";

    if(check(TokenType::Op, "+") || check(TokenType::Op, "-")) {
        debug();
        nextToken();
    }

    term();

    while(check(TokenType::Op, "+") || check(TokenType::Op, "-")) {
        debug();
        nextToken();
        term();
    }
}

/* term = factor {("*"|"/") factor}; */
void Parser::term() {
    tree_pos = "<term>";

    factor();
    while(check(TokenType::Op, "*") || check(TokenType::Op, "/")) {
        debug();
        nextToken();
        factor();
    }
}

/* factor = ident | number | "(" expression ")"; */
void Parser::factor() {
    tree_pos = "<factor>";

    /* ident */
    if(check(TokenType::Ident)) {
        debug();
        nextToken();
    }
    /* number */
    else if(check(TokenType::Num)) {
        debug();

        transpiler.t_num(curr_token.value);

        nextToken();
    }
    /* "(" expression ")" */
    else if(check(TokenType::Op, "(")) {
        debug();
        nextToken();
        expression();
        expect(TokenType::Op, ")");
    }
    else {
        throw std::runtime_error("Syntax error: invalid factor");
    }
}
