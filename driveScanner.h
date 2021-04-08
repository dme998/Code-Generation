#ifndef DRIVESCANNER_H
#define DRIVESCANNER_H
#include <string>
#include "token.h"


/**
 * drives the scanner to lexically analyze a file until EOF
 * @param filename name of file to be run through scanner
 * @return the completed tokens vector
 */
vector<token_t> driver(const std::string &filename);


/**
 * prints the character vector all on the same line
 * @param v char vector
 */
void printLexemes(vector<char> const &v); 


/**
 * prints the token vector, formatted one per line
 * @param v token vector
 */
void printTokens(vector<token_t> const &v);

#endif
