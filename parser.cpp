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
const bool VERBOSE = true;  //set to true to enable verbose print statements throughout run

/**
 * auxillary function that parses tokens according to BNF
 * @return completed parse tree
 */
ParseTree parser() {
  //printf("parser launch\n");
  
  ParseTree mytree;

  mytoken = nextToken();
  nonterminal.fn_program();
  if (mytoken.id == EOF_TK) {
    printf("EOF token received.\nParse OK.\n");
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
  if (VERBOSE) cout << "fetched token: " << token.instance << endl;
  return token;
}


/**
 * show error message when unexpected token in parsing
 * @param exp value expected by parser
 * @param tk token most recently received by parser
 */
void error(string exp, token_t tk) {
  cout << "Error on line " << tk.line << ": " << "expected " << exp << " but received " 
    << TOKENPRINTS[tk.id] << " " << tk.instance << "\nParse failed." << endl;
  exit(1);
};


/**
 * Nonterminal member functions for recursive descent 
 * @return void (explicit)
 */
void Nonterminal :: fn_program() { //done
  //<program> -> <vars> main <block>
  if (VERBOSE) cout << "call fn_program()" << endl;
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
  //<block> -> begin <vars> <stats> end
  if (VERBOSE) cout << "call fn_block()" << endl;
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
  //<vars> -> epsilon | data Identifier := Integer ; <vars>
  if (VERBOSE) cout << "call fn_vars()" << endl;
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
  //<stats> -> <stat> <mStat>
  if (VERBOSE) cout << "call fn_stats()" << endl;
  nonterminal.fn_stat();
  nonterminal.fn_mStat();
  return;
}


void Nonterminal :: fn_mStat() {  //done
  //<mStat> -> epsilon | <stat> <mStat>
  if (VERBOSE) cout << "call fn_mStat()" << endl;
  if (mytoken.instance == "end") {  //epsilon: Follow(mStat)
    //do not consume tokens for follow sets
    return;
  }
  else {
    nonterminal.fn_stat();
    nonterminal.fn_mStat();
  }
} 


void Nonterminal :: fn_stat() {  //done
  //<stat> -> <in> ; | <out> ; | <block> | <if> ; | <loop> ; | <assign> ; | <goto> ; | <label> ;
  if (VERBOSE) cout << "call fn_stat()" << endl;
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "getter") { //First(in)
    nonterminal.fn_in();
    if (mytoken.id == OPERATOR_TK && mytoken.instance == ";") {
      mytoken = nextToken();
      return;
    }
    else error(";", mytoken);
  }
  else if (mytoken.id == KEYWORD_TK && mytoken.instance == "outter") { //First(out)
    nonterminal.fn_out(); 
    if (mytoken.id == OPERATOR_TK && mytoken.instance == ";") {
      mytoken = nextToken();
      return;
    }
    else error(";", mytoken);
  }
  else if (mytoken.id == KEYWORD_TK && mytoken.instance == "begin") {  //First(block)
    nonterminal.fn_block();
    return;
  }
  else if (mytoken.id == KEYWORD_TK && mytoken.instance == "if" ) {  //First(if)
    nonterminal.fn_if();
    if (mytoken.id == OPERATOR_TK && mytoken.instance == ";") {
      mytoken = nextToken();
      return;
    }
    else error(";", mytoken);
  }
  else if (mytoken.id == KEYWORD_TK && mytoken.instance == "loop" ) {  //First(loop)
    nonterminal.fn_loop(); 
    if (mytoken.id == OPERATOR_TK && mytoken.instance == ";") {
      mytoken = nextToken();
      return;
    }
    else error(";", mytoken);
  }
  else if (mytoken.id == KEYWORD_TK && mytoken.instance == "assign" ) {  //First(assign)
    nonterminal.fn_assign();
    if (mytoken.id == OPERATOR_TK && mytoken.instance == ";") {
      mytoken = nextToken();
      return;
    }
    else error(";", mytoken);
  }
  else if (mytoken.id == KEYWORD_TK && mytoken.instance == "proc" ) {  //First(goto)
    nonterminal.fn_goto();
    if (mytoken.id == OPERATOR_TK && mytoken.instance == ";") {
      mytoken = nextToken();
      return;
    }
    else error(";", mytoken);
  }
  else if (mytoken.id == KEYWORD_TK && mytoken.instance == "void" ) {  //First(label)
    nonterminal.fn_label();
    if (mytoken.id == OPERATOR_TK && mytoken.instance == ";") {
      mytoken = nextToken();
      return;
    }
    else error(";", mytoken);
  }
} 


void Nonterminal :: fn_in() {  //done
  //<in> -> getter Identifier
  if (VERBOSE) cout << "call fn_in()" << endl;
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


void Nonterminal :: fn_out() {  //done
  //<out> -> outter <expr>
  if (VERBOSE) cout << "call fn_out()" << endl;
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "outter") {
    mytoken = nextToken();
    nonterminal.fn_expr();
    return;
  }
  else error("outter", mytoken);
}


void Nonterminal :: fn_if() {  //done
  //<if> -> if [ <expr> ] <RO> <expr> ] <stat>
  if (VERBOSE) cout << "call fn_if()" << endl;
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "if") {
    mytoken = nextToken();
    if (mytoken.id == OPERATOR_TK  && mytoken.instance == "[") {
      mytoken = nextToken();
      nonterminal.fn_expr();
      nonterminal.fn_RO();
      nonterminal.fn_expr();
      if (mytoken.id == OPERATOR_TK && mytoken.instance == "]") {
        mytoken = nextToken();
        if (mytoken.id == KEYWORD_TK && mytoken.instance == "then") {
          mytoken = nextToken();
          nonterminal.fn_stat();
          return;
        }
        else error("then", mytoken);
      }
      else error("]", mytoken);
    }
    else error("[", mytoken);
  }
  else error("if", mytoken);
}


void Nonterminal :: fn_loop() {  //done
  //<loop> -> loop [ <expr> <RO> <expr> ] <stat>
  if (VERBOSE) cout << "call fn_loop()" << endl; 
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "loop") {
    mytoken = nextToken();
    if (mytoken.id == OPERATOR_TK && mytoken.instance == "[") {
      mytoken = nextToken();
      nonterminal.fn_expr();
      nonterminal.fn_RO();
      nonterminal.fn_expr();
      if (mytoken.id == OPERATOR_TK && mytoken.instance == "]") {
        mytoken = nextToken();
        nonterminal.fn_stat();
        return;
      }
      else error("]", mytoken);
    }
    else error("[", mytoken);
  }
  else error("loop", mytoken);
}


void Nonterminal :: fn_assign() {  //done
  //<assign> -> assign Identifier := <expr>
  if (VERBOSE) cout << "call fn_assign()" << endl; 
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "assign") {
    mytoken = nextToken();
    if (mytoken.id == IDENTIFIER_TK) {
      mytoken = nextToken();
      if (mytoken.id == OPERATOR_TK && mytoken.instance == ":=") {
        mytoken = nextToken();
        nonterminal.fn_expr();
        return;
      }
      else error(":=", mytoken);
    }
    else error(TOKENPRINTS[IDENTIFIER_TK], mytoken);
  }
  else error("assign", mytoken);
}


void Nonterminal :: fn_goto() {  //done
  //<goto> -> proc Identifier
  if (VERBOSE) cout << "call fn_goto()" << endl; 
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "proc") {
    mytoken = nextToken();
    if (mytoken.id == IDENTIFIER_TK) {
      mytoken = nextToken();
      return;
    }
    else error(TOKENPRINTS[IDENTIFIER_TK], mytoken);
  }
  else error("proc", mytoken);
}


void Nonterminal :: fn_label() {  //done
  //<label> -> void Identifier
  if (VERBOSE) cout << "call fn_label()" << endl; 
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "void") {
    mytoken = nextToken();
    if (mytoken.id == IDENTIFIER_TK) {
      mytoken = nextToken();
      return;
    }
    else error(TOKENPRINTS[IDENTIFIER_TK], mytoken);
  }
  else error("void", mytoken);
}


void Nonterminal :: fn_expr() {  //done
  //<expr> -> <N> - <expr> | <N>
  if (VERBOSE) cout << "call fn_expr()" << endl; 
  nonterminal.fn_N();
  if (mytoken.id == OPERATOR_TK && mytoken.instance == "-") {
    mytoken = nextToken();
    nonterminal.fn_expr();
  }
  else {
    return;
  }
}


void Nonterminal :: fn_N() {  //done
  //<N> -> <A> / <N> | <A> * <N> | <A>
  if (VERBOSE) cout << "call fn_N()" << endl; 
   nonterminal.fn_A();
  if (mytoken.id == OPERATOR_TK && mytoken.instance == "/") {
    mytoken = nextToken();
    nonterminal.fn_N();
  }
  else if (mytoken.id == OPERATOR_TK && mytoken.instance == "*") {
    mytoken = nextToken();
    nonterminal.fn_N();
  }
  else {
    return;
  }
}


void Nonterminal :: fn_A() {  //done
  //<A> -> <M> + <A> | <M>
  if (VERBOSE) cout << "call fn_A()" << endl; 
  nonterminal.fn_M();
  if (mytoken.id == OPERATOR_TK && mytoken.instance == "+") {
    mytoken = nextToken();
    nonterminal.fn_A();
    return;
  }
  else {
    return;
  }
}


void Nonterminal :: fn_M() {  //done
  //<M> -> * <M> | <R>
  if (VERBOSE) cout << "call fn_M()" << endl; 
  if (mytoken.id == OPERATOR_TK && mytoken.instance == "*") {
    mytoken = nextToken();
    nonterminal.fn_M();
    return;
  }
  else {
    nonterminal.fn_R();
    return;
  }
}


void Nonterminal :: fn_R() {  //done
  //<R> -> ( <expr> ) | Identifier | Integer
  if (VERBOSE) cout << "call fn_R()" << endl; 
  if (mytoken.id == OPERATOR_TK && mytoken.instance == "(") {
    mytoken = nextToken();
    nonterminal.fn_expr();
    if (mytoken.id == OPERATOR_TK && mytoken.instance == ")") {
      mytoken = nextToken();
      return;
    }
  }
  else if (mytoken.id == IDENTIFIER_TK) {
    mytoken = nextToken();
    return;
  }
  else if (mytoken.id == INTEGER_TK) {
    mytoken = nextToken();
    return;
  }
}


void Nonterminal :: fn_RO() {  //done
  //<RO> -> => | =< | == | [ == ] | %
  if (VERBOSE) cout << "call fn_RO()" << endl; 
  if (mytoken.id == OPERATOR_TK && mytoken.instance == "=>") {
    mytoken = nextToken();
    return;
  }
  else if (mytoken.id == OPERATOR_TK && mytoken.instance == "=<") {
    mytoken = nextToken();
    return;
  }
  else if (mytoken.id == OPERATOR_TK && mytoken.instance == "==") {
    mytoken = nextToken();
    return;
  }
  else if (mytoken.id == OPERATOR_TK && mytoken.instance == "[" ) {
    mytoken = nextToken();
    if (mytoken.id == OPERATOR_TK && mytoken.instance == "==") {
      mytoken = nextToken();
      if (mytoken.id == OPERATOR_TK && mytoken.instance == "]") {
        mytoken = nextToken();
        return;
      }
      else error("]", mytoken);
    }
    else error("==", mytoken);
  }
  else if (mytoken.id == OPERATOR_TK && mytoken.instance == "%") {
    mytoken = nextToken();
    return;
  }
  else error(TOKENPRINTS[OPERATOR_TK], mytoken);
}
