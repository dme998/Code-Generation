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

/**
 * auxillary function that parses tokens according to BNF
 * @return completed parse tree
 */
ParseTree parser() {
  printf("parser launch\n");
  
  Nonterminal nonterminal;
  ParseTree mytree;
  token_t mytoken;

  mytoken = nextToken();
  nonterminal.fn_program();
  if (mytoken.id == EOF_TK) {
    printf("EOF token received\n");
    return mytree;
  }
  else {
    printf("Error: EOF_TK expected, not received. Terminating.\n");
    exit(1);
  }

}


/**
 * gets next token from global tokens vector and then iterates global vector index
 * @return next token in the vector
 */
token_t nextToken() {
  token_t token = gtokens_v.at(vindex);
  vindex++;
  return token;
}

void Nonterminal :: fn_program() {

}

void Nonterminal :: fn_block() {
  
} 

void Nonterminal :: fn_vars() {

}

void Nonterminal :: fn_stats() {

}

void Nonterminal :: fn_mStat() {

} 

void Nonterminal :: fn_stat() {
  
} 

void Nonterminal :: fn_in() {

}
