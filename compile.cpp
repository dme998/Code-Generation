/* Project:        Code Generation (P4)
 * Filename:       compile.cpp
 * Description:    Generates code after lexical analysis, parsing, and semantics analysis
 * Author:         Daniel Eggers <dme998@mail.umsl.edu>
 * Course:         Program Translation (CS4280-001)
 * Instructor:     Mark Hauschild
 * Date:           May 8, 2021 
 * All Files:      main.cpp parser.cpp parser.h driveScanner.cpp driveScanner.h 
                   scanner.cpp scanner.h ptree.h token.h semantics.cpp semantics.h
                   compile.cpp compile.h
 */
#include <iostream>
#include "compile.h"
#include "ptree.h"
#include "token.h"

using std::cout;
using std::endl;

const bool VERBOSE = true;

void compile(Node* mytree) {
  if (VERBOSE) cout << "Code generation start." << endl;

}
