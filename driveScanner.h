/* Project:        Parser and Tree Builder (P2)
 * Filename:       driveScanner.h
 * Description:    prefilter drives scanner and builds a vector from the resulting tokens
 * Author:         Daniel Eggers <dme998@mail.umsl.edu>
 * Course:         Program Translation (CS4280-001)
 * Instructor:     Mark Hauschild
 * Date:           April 12, 2021 
 * All Files:      main.cpp parser.cpp parser.h driveScanner.cpp driveScanner.h 
                   scanner.cpp scanner.h ptree.h token.h
 */

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