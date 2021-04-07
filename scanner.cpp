#include <iostream>
#include <algorithm>  //std::all_of
#include "scanner.h"
#include "testScanner.h"
#include "token.h"

using std::cout;  using std::endl;
using std::string;

/**
 * returns one token 
 * @param input filtered string to be lexically analyzed
 * @param line current line number of the file that the token is on
 * @return token 
 */
token_t lex(string input, unsigned int line) {
  //cout << "Scanner called." << endl;

  token_t token;
  
  //default values
  token.id = UNKNOWN_TK;
  token.instance = input;
  token.line = line;
  //cout << "Lexing input: " << input << endl;


  //determine tokenID and return
  
  //is whitespace?
  if (  std::all_of( input.begin(), input.end(), isspace )  ) {
    token.id = WHITESPACE_TK;
    return token;
  }

  //is operator?
  for(size_t i=0; i<OPERATORS.size(); i++) {
    if (input == OPERATORS[i]) {
      token.id = OPERATOR_TK;
      return token;
    }
  }

  //is integer?
  if (isInteger(input)) {
    token.id = INTEGER_TK;
    return token;
  }

  //is keyword? 
  for(size_t i=0; i<KEYWORDS.size(); i++) {
    if (input == KEYWORDS[i]) {
      token.id = KEYWORD_TK;
      return token;
    }
  }

  //is identifier?
  if (isIdentifier(input)) {
    token.id = IDENTIFIER_TK;
    return token;
  }

  //cout << "Scanner done." << endl;
  return token;
}


/**
 * return true if input meets INTEGER_TK criteria
 * @param input the string to examine
 */
bool isInteger(string input) {
  for (unsigned int i=0; i<input.length(); i++) {
      if ( !isdigit(input[i]) ) {
        return false;
      }
  }
  return true;
}


/**
 * return true if input meets IDENTIFIER_TK criteria
 * @param input the string to be examined
 */
bool isIdentifier(string input) {
  //first char must be underscore or lowercase letter
  if ( islower(input[0]) || input[0] == '_' ) {
    //must continue with any number of letters (uppercase or lowercase) or digits
    for (unsigned int i=1; i<input.length(); i++) {
      if ( !isalnum(input[i]) ) {
        return false;
      }
    }
  }
  else {
    return false;
  }
  return true;
}
