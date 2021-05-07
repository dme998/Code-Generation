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


/* auxillary function to code generation and storage allocation
 * @param mytree the root node to the previously generated parse tree
 * @param infile is the filename of the source code with .fs extension
 */
void compile(Node* mytree, std::string infile) {
  if (VERBOSE) cout << "Code generation start." << endl;
  
  string targetName = swapFileExtension(infile);  

  //Code Generation (ends with STOP)
  ofstream ASMFILE;
  ASMFILE.open(targetName);
  ASMFILE << "STOP\n";
  ASMFILE.close();
  
  //Storage Allocation (post-STOP)
  
  if (VERBOSE) cout << "Code generation end." << endl;
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

