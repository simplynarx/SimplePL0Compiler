#include <lexer.hpp>

std::vector<std::string> keywords = {"begin",     "end", "if",    "then",
                                     "while",     "do",  "const", "var",
                                     "procedure", "odd", "call"};

Lexer::Lexer(const std::string &fname) {
    src = read_file(fname);
    pos = 0;
}

/**
 * read_file - read in file for lexing and parsing
 *
 * args:
 * fname - input file name (taken from argv)
 */
std::vector<char> Lexer::read_file(std::string fname) {
    std::vector<char> src;

    //Check filename for appropriate extension
    if(fname.find('.') == std::string::npos) {
        std::cerr << "error: file must end in .pl0" << std::endl;
        exit(1);
    }

    if(fname.find(".pl0") == std::string::npos) {
        std::cerr << "error: file must end in .pl0" << std::endl;
        exit(1);
    }

    //Open file, starting on the last character
    std::ifstream fp(fname, std::ios::ate | std::ios::binary);

    //Check file for errors
    if(!fp) {
        std::cerr << "error: file could not be opened" << std::endl;
        exit(1);
    }

    auto size = fp.tellg();
    fp.seekg(0, std::ios::beg);

    if(size == 0) {
        std::cerr << "error: file is empty" << std::endl;
        exit(1);
    }

    src.resize(size);

    if(!fp.read(src.data(), size)) {
        std::cerr << "error: could not read file" << std::endl;
    }

    fp.close();

    return src;
}

/**
 * peek - check the character at the current position in
 * the input stream
 *
 * returns:
 * char - the character at current position in input stream
 */
char Lexer::peek() {
    return (pos < src.size() ? src.at(pos) : '\0');
}

/**
 * get_next_char - check the character at the next position
 * in the input stream
 *
 * returns:
 * char - the character at the next position in the input stream
 */
char Lexer::get_next_char() {
    return (pos < src.size() ? src.at(pos++) : '\0');
}

/**
 * is_keyword - checks if argument is a keyword
 *
 * args:
 * word - the word being looked for
 *
 * returns:
 * true if word is found, false otherwise
 */
bool Lexer::is_keyword(const std::string &word) {
    auto it = std::find(keywords.begin(), keywords.end(), word);
    if(it != keywords.end()) return true;
    else return false;
}

/**
 * get_next_token - determines and returns the next token in
 * the input stream
 *
 * returns:
 * Token - the next token in the input stream
 */
Token Lexer::get_next_token() {
    //first removes any whitespace at the beginning
    //of the file
    while(std::isspace(peek())) {
        get_next_char();
    }

    char currChar = peek();

    //checks for EOF
    if(currChar == '\0') {
        return {TokenType::EndOfFile, ""};
    }

    //checks for an identifier or keyword
    if(std::isalpha(currChar)) {
        std::string ident;

        while(std::isalnum(peek())) {
            ident += get_next_char();
        }

        if(is_keyword(ident)) {
            return {TokenType::Keyword, ident};
        }
        else {
            return {TokenType::Ident, ident};
        }
    }

    //checks for a number
    if(std::isdigit(currChar)) {
        std::string num;

        while(std::isdigit(peek())) {
            num += get_next_char();
        }
        return {TokenType::Num, num};
    }

    //checks for an operator
    if(std::ispunct(currChar)) {
        std::string op(1, get_next_char());
        return {TokenType::Op, op};
    }

    //otherwise return an invalid token
    return {TokenType::Invalid, std::string(1, get_next_char())};
}

/**
 * tokenize - returns all tokens from the input stream
 *
 * returns:
 * std::vector<Token> - a vector contianing all tokens from
 * the input stream
 */
std::vector<Token> Lexer::tokenize() {
    Token t;
    std::vector<Token> tokens;

    while(true) {
        t = get_next_token();

        if(t.type == TokenType::EndOfFile) {
            tokens.push_back(t);
            break;
        }

        if(t.type == TokenType::Invalid) break;
        tokens.push_back(t);
    }

    return tokens;
}

/**
 * print_tokens - prints all tokens from the input stream
 */
void Lexer::print_tokens(const std::vector<Token> &tokens) {
    std::cout << "\033[4mTokens\033[0m\n" << std::endl;

    for(const Token &token : tokens) {
        std::string type;

        switch(token.type) {
            case TokenType::Ident : type = "Ident"; break;
            case TokenType::Num : type = "Num"; break;
            case TokenType::Keyword : type = "Keyword"; break;
            case TokenType::Op : type = "Op"; break;
            case TokenType::EndOfFile : type = "EOF"; break;
            case TokenType::Invalid : type = "Invalid"; break;
        }

        std::cout << "Type: " << type << "\tValue: " << token.value << std::endl;
    }
}
