/* Project:        Code Generation (P4)
 * Filename:       compile.h
 * Description:    Generates code after lexical analysis, parsing, and semantics analysis
 * Author:         Daniel Eggers <dme998@mail.umsl.edu>
 * Course:         Program Translation (CS4280-001)
 * Instructor:     Mark Hauschild
 * Date:           May 8, 2021 
 * All Files:      main.cpp parser.cpp parser.h driveScanner.cpp driveScanner.h 
                   scanner.cpp scanner.h ptree.h token.h semantics.cpp semantics.h
                   compile.cpp compile.h
 */

#ifndef COMPILE_H
#define COMPILE_H
#include "ptree.h"
#include "token.h"

void compile(Node* mytree, std::string infile);
std::string swapFileExtension(std::string filename);

#endif
