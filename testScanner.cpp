#include <iostream>
#include <fstream>
#include "testScanner.h"
#include "scanner.h"
#include "token.h"
using std::cout;    using std::endl;
using std::string;  using std::vector;
using std::ifstream;
const bool DEBUG = false;  //set to true to enable verbose print statements throughout run

/**
 * drives the scanner to lexically analyze a file until EOF and prints tokens to console
 * @param filename name of file to be run through scanner
 * @return 0 if success, -1 if error
 */
int driver(const std::string &filename) {
  //cout << "Driver start." << endl;
  
  vector<token_t> tokens_v;  //vector to hold all tokens received by scanner
  //vector<char> chars_v;      //vector to hold individual characters
  token_t token;
  string wipstring;  //work-in-progress string to be appended-to before being passed to scanner

  //open file for reading
  ifstream infile(filename);  
  if (infile.is_open()) {
    if (DEBUG) cout << "File open success." << endl;
  }
  else {
    cout << "File open error." << endl;
    return -1;
  }
  
  /* read through file char by char, filtering comments and whitespace,
   * building a string to pass to the scanner */
  char c, cc;
  unsigned int line = 1;  //current line number of the file that the token is on
  bool addLine = false;   //flag that tells program to increment line count after pushing token
  bool inComment = false; //flag true to ignore characters until we find "$$"
  bool building = true;   //flag false once the string is built and ready to be scanned
  while(infile.get(c)) {
    if (DEBUG) cout << "c: " << c << endl;
    building = true;
    if (building) {
      if (DEBUG) cout << "top of switch(" << c << ");" << endl;
      switch(c) {
        case '$':
          if (DEBUG) cout << "case $" << endl;
          infile.get(cc);
          if (DEBUG) cout << "cc: " << cc << endl;
          if (cc == '$') {
            if (!inComment) {
              inComment = true;
              if (DEBUG) cout << "inComment = true\n";
            }
            else if (inComment) {
              inComment = false;
              if (DEBUG) cout << "inComment = false\n";
            }
          }
          else if (!inComment) {
            wipstring.push_back(c);
            if (DEBUG) cout << "wipstring push_back(" << c << ");" << endl;
          }
          break;
        case ' ':
          if (DEBUG) cout << "case ws." << endl;
          if (!inComment) {
            if (DEBUG) cout << "ws-newline marks end of build." << endl;
            building = false;
          }
          break;
        case '\n':
          if (DEBUG) cout << "case newline." << endl;
          if (DEBUG) cout << "line = " << line << endl;
          if (!inComment) {
            addLine = true;   
            if (DEBUG) cout << "ws-newline marks end of build." << endl;
            building = false;
          }
          else {
            line++;
          }
          break;
        default:
          if (!inComment) {
            if (DEBUG) cout << "case default." << endl;
            wipstring.push_back(c);
            if (DEBUG) cout << "wipstring push_back(" << c << ");" << endl;
          }
          break;
      }
    } 
    //if we're done building, let's pass the assembled string and tokenize it:
    if (building == false) {
      if (DEBUG) cout << "lex(" << wipstring << ");" << endl;
      
      token = lex(wipstring, line);
      if (token.id == UNKNOWN_TK) {
        cout << "Error: unrecognized token  " << token.instance << "  on line " << token.line << ".\n";
        return -1;
      }
      if (token.id != WHITESPACE_TK) {
        tokens_v.push_back(token);
      }
      wipstring = "";  //empty out string so we can build the next one
      if (addLine) line++;  //increment line number if newline char was found earlier
      addLine = false;
    }
    
  }
  infile.close(); 
  if (DEBUG) cout << "File closed." << endl;
  

  //print vector of tokens
  if (DEBUG) cout << "\nPrinting final tokens vector:" << endl;
  printTokens(tokens_v);
  

  //cout << "Driver end." << endl;
  return 0;
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

