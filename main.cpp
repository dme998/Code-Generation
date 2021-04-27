/* Project:        Parser and Tree Builder (P2)
 * Filename:       main.cpp
 * Description:    source file for executable
 * Author:         Daniel Eggers <dme998@mail.umsl.edu>
 * Course:         Program Translation (CS4280-001)
 * Instructor:     Mark Hauschild
 * Date:           April 12, 2021 
 * All Files:      main.cpp parser.cpp parser.h driveScanner.cpp driveScanner.h 
                   scanner.cpp scanner.h ptree.h token.h
 */

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>  //for STDOUT_FILENO
#include <fstream>

#include "token.h"
#include "scanner.h"
#include "driveScanner.h"
#include "parser.h"
#include "semantics.h"

using std::cout;
using std::endl;
using std::ofstream;

string implicitFileExtension(string filename);
bool fileExists(string filename);
vector<token_t> gtokens_v;
const bool VERBOSE = false; //set to true to enable verbose print statements throughout run


/**
 * Main executable to run
 * @param argv name of file to be run through scanner
 * @return 0 on success, 1 on nonfatal error, -1 on fatal error
 */
int main(int argc, char *argv[]) {
  //cout << "Program start." << endl;
  
  string infile;  //this will be the filename with extension
  switch(argc) {
    case 1: {
      cout << "No file specified. Using stdin.  Enter 'stop' when finished:" << endl;

      string sin;
      const string tempfile = "tmp.fs";
      ofstream myfile(tempfile);
      while(std::getline(std::cin, sin)) {
        if (sin == "stop") {
          infile = (tempfile);
          break;
        }
        else {
          myfile << sin << endl;
        }
      }
      myfile.close();
      break;
    }
    case 2: {
      infile = implicitFileExtension((string)argv[1]);
      if (fileExists(infile)) {
        //cout << "File exists: " << infile << endl;
      }
      else {
        cout << "File not found: " << infile << endl;
        exit(0);
      }
      break;
    }
    default:
      cout << "Improper invocation: wrong number of arguments." << endl;
      exit(0);
      break;
  }
  
  //run driveScanner driver to build final tokens vector
  driver(infile);
  
  //print tokens vector 
  if (VERBOSE) {
    cout << "TOKENS:" << endl;
    printTokens(gtokens_v);
  }

  //parse tokens vector
  Node* mytree = addNode("tree");
  mytree = parser();
  
  mytree->print(mytree, 0);

  //semantics analysis
  semantics(mytree);

  return 0;
}


/**
 * Appends .fs extension to filename if not provided
 * @param filename specifies infile
 * @return filename with .fs extension
 */
string implicitFileExtension(string filename) {
  if (filename.substr(filename.find_last_of(".") + 1) != "fs") {
    filename.append(".fs");
  }
  return filename;
}


/**
 * Check if file exists
 * @param filename to check
 * @return true if exists, otherwise false
 */
bool fileExists(string infile) {
  if (FILE *file = fopen(infile.c_str(), "r")) {
    fclose(file);
    return true;
  }
  else {
    return false;
  }
}

