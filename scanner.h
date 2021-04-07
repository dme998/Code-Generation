#ifndef SCANNER_H
#define SCANNER_H
#include <string>
#include "token.h"

/**
 * returns one token 
 * @param filename name of file to be run through scanner
 * @param line current line number of the file that the token is on
 * @return token
 */
token_t lex(std::string input, unsigned int line);


/**
 * return true if input meets INTEGER_TK criteria
 * @param input the string to examine
 */
bool isInteger(std::string input);


/**
 * return true if input meets IDENTIFIER_TK criteria
 * @param input the string to be examined
 */
bool isIdentifier(string input);


#endif
