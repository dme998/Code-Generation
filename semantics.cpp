/* Project:        Static Semantics (P3)
 * Filename:       semantics.cpp
 * Description:    Performs static semantics analysis on parse tree 
 * Author:         Daniel Eggers <dme998@mail.umsl.edu>
 * Course:         Program Translation (CS4280-001)
 * Instructor:     Mark Hauschild
 * Date:           April 26, 2021 
 * All Files:      main.cpp parser.cpp parser.h driveScanner.cpp driveScanner.h 
                   scanner.cpp scanner.h ptree.h token.h semantics.cpp semantics.h
 */

#include <vector>
#include "semantics.h"
#include "token.h"
#include "ptree.h"

using std::vector;

/* performs static semantics analysis
 * @param mytree the root node to the previously generated parse tree
 */
 void semantics() {
     vector<token_t> identifiers_v;  //symbol table that holds variable identifiers 
     
 }