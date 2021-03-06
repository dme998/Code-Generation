/* Project:        Parser and Tree Builder (P2)
 * Filename:       driveScanner.cpp
 * Description:    prefilter drives scanner and builds a vector from the resulting tokens
 * Author:         Daniel Eggers <dme998@mail.umsl.edu>
 * Course:         Program Translation (CS4280-001)
 * Instructor:     Mark Hauschild
 * Date:           April 12, 2021 
 * All Files:      main.cpp parser.cpp parser.h driveScanner.cpp driveScanner.h 
                   scanner.cpp scanner.h ptree.h token.h
 */

#include <iostream>
#include <fstream>
#include <unistd.h>  //for STDOUT_FILENO
#include "driveScanner.h"
#include "scanner.h"
#include "token.h"
using std::cout;    using std::endl;
using std::string;  using std::vector;
using std::ifstream;

const bool VERBOSE = false;  //set to true to enable verbose print statements throughout run


/**
 * drives the scanner to lexically analyze a file until EOF and prints tokens to console
 * @param filename name of file to be run through scanner
 * @return the completed tokens vector
 */
void driver(const std::string &filename) {
  if (VERBOSE) cout << "Driver start." << endl;
  
  token_t token;
  string wipstring;  //work-in-progress string to be appended-to before being passed to scanner

  //open file for reading
  ifstream infile(filename);  
  if (infile.is_open()) {
    if (VERBOSE) cout << "File open success." << endl;
  }
  else {
    cout << "File open error." << endl;
    write(STDOUT_FILENO, "File open error. Terminating.\n", 30);
    exit(1);
  }
  
  /* read through file char by char, filtering comments and whitespace,
   * building a string to pass to the scanner */
  char c, cc;
  unsigned int line = 1;  //current line number of the file that the token is on
  bool addLine = false;   //flag that tells program to increment line count after pushing token
  bool inComment = false; //flag true to ignore characters until we find "$$"
  bool building = true;   //flag false once the string is built and ready to be scanned
  while(infile.get(c)) {
    if (VERBOSE) cout << "c: " << c << endl;
    building = true;
    if (building) {
      if (VERBOSE) cout << "top of switch(" << c << ");" << endl;
      switch(c) {
        case '$':
          if (VERBOSE) cout << "case $" << endl;
          infile.get(cc);
          if (VERBOSE) cout << "cc: " << cc << endl;
          if (cc == '$') {
            if (!inComment) {
              inComment = true;
              if (VERBOSE) cout << "inComment = true\n";
            }
            else if (inComment) {
              inComment = false;
              if (VERBOSE) cout << "inComment = false\n";
            }
          }
          else if (!inComment) {
            wipstring.push_back(c);
            if (VERBOSE) cout << "wipstring push_back(" << c << ");" << endl;
          }
          break;
        case ' ':
          if (VERBOSE) cout << "case ws." << endl;
          if (!inComment) {
            if (VERBOSE) cout << "ws-newline marks end of build." << endl;
            building = false;
          }
          break;
        case '\n':
          if (VERBOSE) cout << "case newline." << endl;
          if (VERBOSE) cout << "line = " << line << endl;
          if (!inComment) {
            addLine = true;   
            if (VERBOSE) cout << "ws-newline marks end of build." << endl;
            building = false;
          }
          else {
            line++;
          }
          break;
        default:
          if (!inComment) {
            if (VERBOSE) cout << "case default." << endl;
            wipstring.push_back(c);
            if (VERBOSE) cout << "wipstring push_back(" << c << ");" << endl;
          }
          break;
      }
    } 
    //if we're done building, let's pass the assembled string and tokenize it:
    if (building == false) {
      if (VERBOSE) cout << "tokenize(" << wipstring << ");" << endl;
      
      token = tokenize(wipstring, line);
      if (token.id == UNKNOWN_TK) {
        cout << "Error:  " << token.instance << "  on line " << token.line << ".\n";
        write(STDOUT_FILENO, "Unrecognized token.  Terminating.\n", 34);
        exit(1);
      }
      if (token.id != WHITESPACE_TK) {
        gtokens_v.push_back(token);
      }
      wipstring = "";  //empty out string so we can build the next one
      if (addLine) line++;  //increment line number if newline char was found earlier
      addLine = false;
    }
    
  }//end of while loop
  infile.close(); 
  if (VERBOSE) cout << "File closed." << endl;
  
  //add EOF token to finalize the vector
  token.id = EOF_TK;
  token.instance = "\u0000";
  token.line = line;
  gtokens_v.push_back(token);
  if (VERBOSE) cout << "Added EOF token to final vector." << endl;  
  if (VERBOSE) cout << "Driver end." << endl;
}


/**
 * prints the character vector on a single line
 * @param v character vector
 */
void printLexemes(vector<char> const &v) {
  for(unsigned int i=0; i<v.size(); i++) {
    cout << v.at(i);
  }
  cout << endl;
}


/**
 * prints the token vector, formatted one per line
 * @param v token vector
 */
void printTokens(vector<token_t> const &v) {
  for(unsigned int i=0; i<v.size(); i++) {
    //TOKENPRINTS[tokenID_e] to print token description (see token header file)
    cout << "{" << TOKENPRINTS[ v[i].id ] << ", " << v[i].instance << ", " << v[i].line << "}\n";
  }
}


