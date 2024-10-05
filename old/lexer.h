#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

typedef enum {
  TK_IDENT,
  TK_NUMBER,
  TK_CONST,
  TK_VAR,
  TK_PROCEDURE,
  TK_CALL,
  TK_BEGIN,
  TK_END,
  TK_IF,
  TK_THEN,
  TK_WHILE,
  TK_DO,
  TK_ODD,
  TK_DOT,
  TK_EQUAL,
  TK_COMMA,
  TK_SEMICOLON,
  TK_ASSIGN,
  TK_HASH,
  TK_LESSTHAN,
  TK_GREATERTHEN,
  TK_PLUS,
  TK_MINUS,
  TK_MULTIPLY,
  TK_DIVIDE,
  TK_LEFTPAREN,
  TK_RIGHTPAREN
} TokenType;

void error(std::string err);
void read_file(std::string fname);
