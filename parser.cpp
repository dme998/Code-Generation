/* Project:        Parser and Tree Builder (P2)
 * Filename:       parser.cpp
 * Description:    parses tokens according to BNF specified in README
 * Author:         Daniel Eggers <dme998@mail.umsl.edu>
 * Course:         Program Translation (CS4280-001)
 * Instructor:     Mark Hauschild
 * Date:           April 12, 2021 
 * All Files:      main.cpp parser.cpp parser.h driveScanner.cpp driveScanner.h 
                   scanner.cpp scanner.h ptree.h token.h
 */

#include "token.h"
#include "scanner.h"
#include "driveScanner.h"
#include "parser.h"
#include "ptree.h"

static int vindex = 0;  //vindexition in the tokens vector (vector index)
static token_t mytoken;  //dynamic token
static Nonterminal nonterminal;  //for access to nonterminal functions

/**
 * auxillary function that parses tokens according to BNF
 * @return completed parse tree
 */
ParseTree parser() {
  printf("parser launch\n");
  
  ParseTree mytree;

  mytoken = nextToken();
  nonterminal.fn_program();
  if (mytoken.id == EOF_TK) {
    printf("EOF token received. Parse OK.\n");
    return mytree;
  }
  else {
    printf("Error: EOF_TK expected, not received. Terminating.\n");
    exit(1);
  }
  
  return mytree;
}


/**
 * gets next token from global tokens vector and then iterates global vector index
 * @return next token in the vector
 */
token_t nextToken() {
  token_t token = gtokens_v.at(vindex);
  vindex++;
  cout << "fetched token: " << token.instance << endl;
  return token;
}


void error(string exp, token_t tk) {
  cout << "Error on line " << tk.line << ": " << "expected " << exp << " but received " 
    << TOKENPRINTS[tk.id] << " " << tk.instance << ". Parse failed." << endl;
  exit(1);
};


/* Nonterminal member functions */
void Nonterminal :: fn_program() { //done
  cout << "call fn_program()" << endl;
  nonterminal.fn_vars();
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "main") {
    mytoken = nextToken();
    nonterminal.fn_block();
    return;
  }
  else {
    error("main", mytoken);
  }
}


void Nonterminal :: fn_block() {  //done
  cout << "call fn_block()" << endl;
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "begin") {
    mytoken = nextToken();
    nonterminal.fn_vars();
    nonterminal.fn_stats();
    if (mytoken.id == KEYWORD_TK && mytoken.instance == "end") {
      mytoken = nextToken();
      return;
    }
    else error("end", mytoken);
    return;
  }
  else error("begin", mytoken);
}


void Nonterminal :: fn_vars() {  //done
  cout << "call fn_vars()" << endl;
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "main") {  //epsilon: Follow(vars)
    //do not consume tokens for follow sets
    return;
  }

  if (mytoken.instance == "data") {
    mytoken = nextToken();
    if (mytoken.id == IDENTIFIER_TK) {
      mytoken = nextToken();
      if (mytoken.id == OPERATOR_TK && mytoken.instance == ":=") {
        mytoken = nextToken();
        if (mytoken.id == INTEGER_TK) {
          mytoken = nextToken();
          if (mytoken.id == OPERATOR_TK && mytoken.instance == ";") {
            mytoken = nextToken();
            nonterminal.fn_vars();
            return;
          }
          else error(";", mytoken);
        }
        else error(TOKENPRINTS[INTEGER_TK], mytoken);
      }
      else error(":=", mytoken);
    }
    else error(TOKENPRINTS[IDENTIFIER_TK], mytoken);
  }

}


void Nonterminal :: fn_stats() {  //done
  cout << "call fn_stats()" << endl;
  nonterminal.fn_stat();
  nonterminal.fn_mStat();
  return;
}


void Nonterminal :: fn_mStat() {  //done
  cout << "call fn_mStat()" << endl;
  if (mytoken.instance == "end") {  //epsilon: Follow(mStat)
    //do not consume tokens for follow sets
    return;
  }
  else {
    nonterminal.fn_stat();
    nonterminal.fn_mStat();
  }
} 


void Nonterminal :: fn_stat() {  //TODO
   cout << "call fn_stat()" << endl;
   nonterminal.fn_in();
   if (mytoken.id == OPERATOR_TK && mytoken.instance == ";") {
     mytoken = nextToken();
     return;
   }
   else error(";", mytoken);
   //else if... <out>; | <block> | <if>; | <loop>; | <assign>; | <goto>; | <label>;
} 


void Nonterminal :: fn_in() {  //done
  cout << "call fn_in" << endl;
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "getter") {
    mytoken = nextToken();
    if (mytoken.id == IDENTIFIER_TK) {    
      mytoken = nextToken();
      return;
    }
    else error(TOKENPRINTS[IDENTIFIER_TK], mytoken);
  }
  else error("getter", mytoken);
}
