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
using std::vector;

const bool VERBOSE = false;
string targetName;  // asm file to write-to
ofstream ASMFILE;
string parent;  // global helper string for tracking parent productions across recursion
string tmpinstance;

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
  if (VERBOSE) cout << "FOR:" << endl;
    for (int i = 0; i < (int)gstv.size(); i++) {
      if (VERBOSE) cout << ":" << gstv.at(i).token.instance << endl;
      if (gstv.at(i).token.id == IDENTIFIER_TK && gstv.at(i).isData)
        ASMFILE << gstv.at(i).token.instance << " 0\n";
    }
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
    if (leafsize >= 4) {  
      ASMFILE << "ADD " << node->leaves_v.at(3).instance << "\n"
      << "STORE " << node->leaves_v.at(1).instance << "\n"
      << "SUB " << node->leaves_v.at(1).instance << "\n";
    }
    else if (leafsize == 0) {
      ASMFILE << "\n";
    }
  }
  else if (label == "expr") {
    // possible leaves: -
    if (leafsize == 1) {
      //<N> - <expr>
      cout << "Warning: <expr> expression could not be translated." << endl;
    }
    else {
      //continue to <N>
    }
  }
  else if (label == "N") {
    // possible leaves: / or *
    if (leafsize == 1) {
      //<A> / <N> or <A> * <N>
      if (node->leaves_v.at(0).instance == "*") {
        cout << "Warning: <A> * <N> operation could not be translated." << endl;
      }
      else if (node->leaves_v.at(0).instance == "/") {
        cout << "Warning: <A> / <N> operation could not be translated." << endl;
      }
    }
    else {
      //continue to <A>
    }
  }
  else if (label == "A") {
    // possible leaves: +
    if (leafsize == 1) {
      // <M> + <A>
      cout << "Warning: <A> + <A> operation could not be translated." << endl;
    }
    else {
      //continue to <M>
    }
  }
  else if (label == "M") {
    // possible leaves: *
    if (leafsize == 1) {
      // * <M>
      cout << "Warning: <M> operation could not be translated." << endl;
    }
    else {
      //continue to <R>
    }
  }
  else if (label == "R") {
    // possible leaves: ( ) or Identifier or Integer
    if (leafsize == 2) {
      cout << "Warning: <R> operation could not be translated." << endl;
    }
    else if (leafsize == 1) {
      //Identifier or Integer
      if (parent == "outter <expr>") { 
        ASMFILE << "WRITE " << node->leaves_v.at(0).instance << "\n";
      }
      else if (parent == "assign") {
        ASMFILE << "ADD " << node->leaves_v.at(0).instance << "\n"
        << "STORE " << tmpinstance << "\n"
        << "SUB " << node->leaves_v.at(0).instance << "\n";
      }
      else {
        ASMFILE << "NOOP\n";
      }
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
  else if (label == "assign") {
    // possible leaves: assign Identifier :=
    parent = "assign";
    tmpinstance = node->leaves_v.at(1).instance;
    //continue to <expr>
  }
  else if (label == "in") {
    // possible leaves: getter var
    if (leafsize == 2) {
      ASMFILE << "READ " << node->leaves_v.at(1).instance << "\n";
    }
  }
  else if (label == "out") {
    // possible leaves: outter 
    parent = "outter <expr>";
  }
  else if (label == "if") {
    cout << "Warning: <if> statement could not be translated." << endl;
  }
  else if (label == "loop") {
    cout << "Warning: <loop> statement could not be translated." << endl;
  }
  else if (label == "RO") {
    //cout << "Warning: <RO> operation could not be translated." << endl;
  }
  else if (label == "label") {
    // void Identifier
    if (leafsize >= 2) { 
      ASMFILE << node->leaves_v.at(1).instance << ": NOOP\n";
    }
  }
  else if (label == "goto") {
    // proc Identifier
    if (leafsize >= 2) {
      ASMFILE << "BR " << node->leaves_v.at(1).instance << "\n";
    }
  }
  else {
    if (VERBOSE) cout << "Warning: " << label << " not implemented." << endl;
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
