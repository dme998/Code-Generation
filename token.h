#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <vector>
using std::string;
using std::vector;

enum tokenID_e {
  UNKNOWN_TK,    // invalid or unrecognized token that should trigger an error
  WHITESPACE_TK, // whitespace to be ignored, discarded
  IDENTIFIER_TK, // variable begin with lower case letter or underscore
  INTEGER_TK,    // unsigned whole numbers
  OPERATOR_TK,   // = => =< == : := + - * / % . ( ) , { } ; [ ]
  KEYWORD_TK,    // begin end loop whole void exit getter outter main if then assign data proc
  EOF_TK         // end of file
};
/* printing TOKENPRINTS[tokenID_e] will print the token's description */
const string TOKENPRINTS[] = {"Unknown", "Whitespace", "Identifier", "Number", "Operator", "Keyword", "EOF"};

const vector<string> OPERATORS {
  "=", "=>", "=<", "==", ":", ":=", "+", "-", "*", "/",
  "%",  ".",  "(",  ")", ",",  "{", "}", ";", "[", "]"
};

const vector<string> KEYWORDS { 
  "begin", "end", "loop", "whole", "void", "exit", "getter", 
  "outter", "main", "if", "then", "assign", "data", "proc"
};

struct token_t {
  tokenID_e id;
  string instance;
  int line;
};

#endif
