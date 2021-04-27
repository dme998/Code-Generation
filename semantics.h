/* Project:        Static Semantics (P3)
 * Filename:       semantics.h
 * Description:    Performs static semantics analysis on parse tree 
 * Author:         Daniel Eggers <dme998@mail.umsl.edu>
 * Course:         Program Translation (CS4280-001)
 * Instructor:     Mark Hauschild
 * Date:           April 26, 2021 
 * All Files:      main.cpp parser.cpp parser.h driveScanner.cpp driveScanner.h 
                   scanner.cpp scanner.h ptree.h token.h semantics.cpp semantics.h
 */

#ifndef SEMANTICS_H
#define SEMANTICS_H
#include "ptree.h"
#include "token.h"
#include <vector>

extern std::vector<token_t> gtokens_v;

struct STV_t {
  token_t token;
  bool isInit;  // true if identifier follows "data" keyword token
};

void semantics(Node* mytree);
void sweepST(std::vector<STV_t> &dynamic_v);
bool hasDuplicates(std::vector<STV_t> vec);

#endif
