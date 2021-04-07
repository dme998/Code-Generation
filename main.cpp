/* Project:        Parser (P2)
 * Description:    Parser
 * Author:         Daniel Eggers <dme998@mail.umsl.edu>
 * Course:         Program Translation (CS4280-001)
 * Instructor:     Mark Hauschild
 * Date:           April 12, 2021 
 * Dependencies:   parser.cpp, parser.h
 */

#include <iostream>
//#include <vector>
#include <string>
#include <unistd.h>  //for STDOUT_FILENO
#include <fstream>
//#include <stdio.h>  //fopen

#include "token.h"
#include "scanner.h"
#include "testScanner.h"
#include "parser.h"
//#include "node.h"

using namespace std;

string implicitFileExtension(string filename);
bool fileExists(string filename);

/**
 * Main executable to run
 * @param argv name of file to be run through scanner
 * @return 0 on success, 1 on nonfatal error, -1 on fatal error
 */
int main(int argc, char *argv[]) {
  cout << "Program start." << endl;
  
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
 

  //TODO
  //get token vector with scanner
  //print token vector
  //loop through vector, parsing tokens
  //print tree


  cout << "Program end." << endl;
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

