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

#include <iostream>
#include <vector>
#include "semantics.h"
#include "token.h"
#include "ptree.h"
using std::cout;
using std::endl;
using std::vector;

const bool VERBOSE = true; // debug print messages

/* performs static semantics analysis
 * @param mytree the root node to the previously generated parse tree
 */
void semantics(Node* mytree) {
  if (VERBOSE) cout << "Semantics analysis." << endl;
  vector<STV_t> identifiers_v;  //symbol table that holds variable identifiers 
  sweepST(identifiers_v);

  //check for duplicate declarations (two or more identical STV_t instances with isInit=true)
  //check for undeclared variables (any STV_t instances with isInit=false that don't follow 
  //  exactly one instance with isInit=true

  if (hasDuplicates(identifiers_v)) {
    exit(1);
  }
  

  cout << "Semantics OK." << endl;
}


/* sweeps identifiers into the symbol table, ignoring all other parsed tokens
 * @param &dynamic_v is the symbol table that holds var identifiers
 * the STV_t type holds a token and a boolean isInit value that marks
 * identifiers that are initialized vs the ones that aren't
 */
void sweepST(vector<STV_t> &dynamic_v) {
  // this function assumes Parse was successful
  //cout << "Semantics auxillary." << endl;
  for(unsigned int i=0; i<gtokens_v.size(); i++) {
    STV_t mystv;

    if (gtokens_v[i].id == KEYWORD_TK && gtokens_v[i].instance == "data") {
      mystv.token = gtokens_v[i+1];
      mystv.isInit = true;
      dynamic_v.push_back(mystv);
      if (VERBOSE) cout << "data " << mystv.token.instance << ";" << endl;
      i++;
    }
    else if (gtokens_v[i].id == IDENTIFIER_TK) {
      mystv.token = gtokens_v[i];
      mystv.isInit = false;
      dynamic_v.push_back(mystv);
      if (VERBOSE) cout << mystv.token.instance << ";" << endl;
    } 
  }
}


/* checks symbol token vector for duplicate variable declarations
 * and print error message if so
 * @return true if there's a duplicate
 */
bool hasDuplicates(vector<STV_t> vec) {
  token_t tk;
  for(size_t i=0; i<vec.size(); i++) {
    for(size_t j=1; j<vec.size(); j++) {
      
      if ( i != j && vec[i].token.instance == vec[j].token.instance 
           && vec[i].isInit == true && vec[j].isInit == true ) {
        tk = vec[j].token;
        cout << "Error on line " << tk.line << ": " 
          << "Variable " << tk.instance << " was previously declared on line " 
          << vec[i].token.line << "." << endl;
        return true;
      }
    
    }
  }
  return false;
}
