/* Project:        Parser and Tree Builder (P2)
 * Filename:       scanner.h
 * Description:    lexically analyzes a single token
 * Author:         Daniel Eggers <dme998@mail.umsl.edu>
 * Course:         Program Translation (CS4280-001)
 * Instructor:     Mark Hauschild
 * Date:           April 12, 2021 
 * All Files:      main.cpp parser.cpp parser.h driveScanner.cpp driveScanner.h 
                   scanner.cpp scanner.h ptree.h token.h
 */

#ifndef SCANNER_H
#define SCANNER_H
#include <string>
#include "token.h"

/**
 * returns one token triplet
 * @param filename name of file to be run through scanner
 * @param line current line number of the file that the token is on
 * @return token
 */
token_t tokenize(std::string input, unsigned int line);


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
