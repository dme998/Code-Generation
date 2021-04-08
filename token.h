/* Project:        Parser and Tree Builder (P2)
 * Filename:       token.h
 * Description:    defines token triplet and associated descriptors
 * Author:         Daniel Eggers <dme998@mail.umsl.edu>
 * Course:         Program Translation (CS4280-001)
 * Instructor:     Mark Hauschild
 * Date:           April 12, 2021 
 * All Files:      main.cpp parser.cpp parser.h driveScanner.cpp driveScanner.h 
                   scanner.cpp scanner.h ptree.h token.h
 */

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
