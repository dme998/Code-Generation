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
#include <vector>
#include <string>
#include <fstream>
#include "compile.h"
#include "ptree.h"
#include "token.h"

using std::cout;
using std::endl;
using std::string;
using std::ofstream;

const bool VERBOSE = true;
string targetName;  // asm file to write-to
ofstream ASMFILE;

/* auxillary function to code generation and storage allocation
 * @param mytree the root node to the previously generated parse tree
 * @param infile is the filename of the source code with .fs extension
 */
void compile(Node* mytree, std::string infile) {
  if (VERBOSE) cout << "Code generation start." << endl;
  
  targetName = swapFileExtension(infile);  

  //Code Generation (ends with STOP)
  ASMFILE.open(targetName);
  generateCode(mytree, 0);
  ASMFILE << "STOP\n";
  
  //Storage Allocation (post-STOP)
    //TODO write global vars: var value (read through vector)
    cout << "FOR:" << endl;
    for (int i = 0; i < (int)gstv.size(); i++) {
      cout << ":" << gstv.at(i).token.instance << endl;
      if (gstv.at(i).token.id == IDENTIFIER_TK && gstv.at(i).isData)
        ASMFILE << gstv.at(i).token.instance << " 0\n";
    }
    cout << endl;
    ASMFILE.close();
  

  cout << targetName << endl;
  return;
}


/**
 * Converts .fs extension from provided filename to .asm
 * @param filename specifies infile (passed from main)
 * @return filename with .asm extension
 */
string swapFileExtension(string filename) {
  if (filename.substr(filename.find_last_of(".") + 1) == "fs") {
    filename.pop_back();
    filename.pop_back();
    filename.append("asm");
  } 
  else {
    filename.append(".asm");
  }
  if (VERBOSE) cout << "Target file set: " << filename << endl;
  return filename;
}


//recursive function to traverse tree in preorder
void generateCode(Node* node, int level) {
  level++;
  if (node == NULL) { return; }
  //ASMFILE << node->label << "\n";
  

  //check node label, then check its leaves in accordance
  int leafsize = node->leaves_v.size();

  string label = node->label;
  if (label == "program") {
    // possible leaves: main
    // disregard structural tokens, otherwise write to file
    // don't return, still need to call children 
  }
  else if (label == "block") {
    // possible leaves: begin, end 
  }
  else if (label == "vars") {
    // possible leaves: data ID := Int ;
    cout << "vars" << endl;
    for(int i = 0; i < leafsize; i++) {
      cout << "<vars>leaves: " << node->leaves_v.at(i).instance << "\n";
    }
    if (leafsize >= 4) {  
      ASMFILE << "ADD " << node->leaves_v.at(3).instance << "\n"
      << "STORE " << node->leaves_v.at(1).instance << "\n"
      << "WRITE " << node->leaves_v.at(1).instance << "\n";
    }
    else if (leafsize == 0) {
      ASMFILE << "\n";
    }
  }
  else if (label == "stats") {
    // possible leaves: none
  }
  else if (label == "mStat") {
    // possible leaves: none
  }
  else if (label == "stat") {
    // possible leaves: ;
  }
  else if (label == "in") {
    // possible leaves: getter var
    if (leafsize == 2) {
      ASMFILE << "READ " << node->leaves_v.at(1).instance << "\n";
    }
  }
  else if (label == "out") {
    // possible leaves: outter 
    if (leafsize == 1) {
      ASMFILE << "WRITE "; 
    }
  }
  else {
    cout << "Label " << label << " not implemented." << endl;
  }
  

  generateCode(node->n0, level);
  generateCode(node->n1, level);
  generateCode(node->n2, level);
  generateCode(node->n3, level);
  return;
}

/* for reference
  int sz = node->leaves_v.size();
    for(int i = 0; i < sz; i++) {
      cout << "GENCODE " << node->leaves_v.at(i).instance << "\n";
    }
*/
