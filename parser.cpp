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
Node* parser() {
  //printf("parser launch\n");
  
  Node* root;
  mytoken = nextToken();
  root = nonterminal.fn_program();
  if (mytoken.id == EOF_TK) {
    printf("EOF token received.\nParse OK.\n");
    return root;
  }
  else {
    printf("Error: EOF_TK expected, not received. Terminating.\n");
    exit(1);
  }
  
  return root;
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
 * create a new node
 * @param label the calling function's name
 * @return the node
 */
Node* addNode(std::string label) {
  Node* p = new Node();
  p->label = label;
  p->n0 = NULL;
  p->n1 = NULL;
  p->n2 = NULL;
  p->n3 = NULL;
  
  return p;
}


/**
 * Nonterminal member functions for recursive descent 
 * @return either pointer to allocated node with defined properties OR NULL
 */
Node* Nonterminal :: fn_program() { //done
  //<program> -> <vars> main <block>
  if (VERBOSE) cout << "call fn_program()" << endl;
  
  Node* p = addNode("program");
  p->n0 = nonterminal.fn_vars();
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "main") {
    p->token = mytoken;
    mytoken = nextToken();
    p->n1 = nonterminal.fn_block();
    return p;
  }
  else {
    error("main", mytoken);
  }
}


Node* Nonterminal :: fn_block() {  //done
  //<block> -> begin <vars> <stats> end
  if (VERBOSE) cout << "call fn_block()" << endl;

  Node* p = addNode("block");
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "begin") {
    p->token = mytoken;
    mytoken = nextToken();
    p->n0 = nonterminal.fn_vars();
    p->n1 = nonterminal.fn_stats();
    if (mytoken.id == KEYWORD_TK && mytoken.instance == "end") {
      p->token = mytoken;
      mytoken = nextToken();
      return p;
    }
    else error("end", mytoken);
    return p;
  }
  else error("begin", mytoken);
}


Node* Nonterminal :: fn_vars() {  //done
  //<vars> -> epsilon | data Identifier := Integer ; <vars>
  if (VERBOSE) cout << "call fn_vars()" << endl;
  
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "main") {  //epsilon: Follow(vars)
    //do not consume tokens for follow sets
    return NULL;
  }

  Node* p = addNode("vars");
  if (mytoken.instance == "data") {
    p->token = mytoken;
    mytoken = nextToken();
    if (mytoken.id == IDENTIFIER_TK) {
      p->token = mytoken;
      mytoken = nextToken();
      if (mytoken.id == OPERATOR_TK && mytoken.instance == ":=") {
        p->token = mytoken;
        mytoken = nextToken();
        if (mytoken.id == INTEGER_TK) {
          p->token = mytoken;
          mytoken = nextToken();
          if (mytoken.id == OPERATOR_TK && mytoken.instance == ";") {
            p->token = mytoken;
            mytoken = nextToken();
            p->n0 = nonterminal.fn_vars();
            return p;
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


Node* Nonterminal :: fn_stats() {  //done
  //<stats> -> <stat> <mStat>
  if (VERBOSE) cout << "call fn_stats()" << endl;
  
  Node* p = addNode("stats");
  p->n0 = nonterminal.fn_stat();
  p->n1 = nonterminal.fn_mStat();
  return p;
}


Node* Nonterminal :: fn_mStat() {  //done
  //<mStat> -> epsilon | <stat> <mStat>
  if (VERBOSE) cout << "call fn_mStat()" << endl;

  Node* p = addNode("mStat");
  if (mytoken.instance == "end") {  //epsilon: Follow(mStat)
    //do not consume tokens for follow sets
    return NULL;
  }
  else {
    p->n0 = nonterminal.fn_stat();
    p->n1 = nonterminal.fn_mStat();
  }
} 

//TODO HERE ONWARD
Node* Nonterminal :: fn_stat() {  //done
  //<stat> -> <in> ; | <out> ; | <block> | <if> ; | <loop> ; | <assign> ; | <goto> ; | <label> ;
  if (VERBOSE) cout << "call fn_stat()" << endl;

	Node* p = addNode("stat");
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "getter") { //First(in)
    p->n0 = nonterminal.fn_in();
    if (mytoken.id == OPERATOR_TK && mytoken.instance == ";") {
      p->token = mytoken;
			mytoken = nextToken();
      return p;
    }
    else error(";", mytoken);
  }
  else if (mytoken.id == KEYWORD_TK && mytoken.instance == "outter") { //First(out)
    p->n0 = nonterminal.fn_out(); 
    if (mytoken.id == OPERATOR_TK && mytoken.instance == ";") {
      p->token = mytoken;
			mytoken = nextToken();
      return p;
    }
    else error(";", mytoken);
  }
  else if (mytoken.id == KEYWORD_TK && mytoken.instance == "begin") {  //First(block)
    p->n0 = nonterminal.fn_block();
    return p;
  }
  else if (mytoken.id == KEYWORD_TK && mytoken.instance == "if" ) {  //First(if)
    p->n0 = nonterminal.fn_if();
    if (mytoken.id == OPERATOR_TK && mytoken.instance == ";") {
      p->token = mytoken;
			mytoken = nextToken();
      return p;
    }
    else error(";", mytoken);
  }
  else if (mytoken.id == KEYWORD_TK && mytoken.instance == "loop" ) {  //First(loop)
    p->n0 = nonterminal.fn_loop(); 
    if (mytoken.id == OPERATOR_TK && mytoken.instance == ";") {
      p->token = mytoken;
			mytoken = nextToken();
      return p;
    }
    else error(";", mytoken);
  }
  else if (mytoken.id == KEYWORD_TK && mytoken.instance == "assign" ) {  //First(assign)
    p->n0 = nonterminal.fn_assign();
    if (mytoken.id == OPERATOR_TK && mytoken.instance == ";") {
      p->token = mytoken;
			mytoken = nextToken();
      return p;
    }
    else error(";", mytoken);
  }
  else if (mytoken.id == //set to true to enable verbose print statements throughout run
KEYWORD_TK && mytoken.instance == "proc" ) {  //First(goto)
    p->n0 = nonterminal.fn_goto();
    if (mytoken.id == OPERATOR_TK && mytoken.instance == ";") {
      p->token = mytoken;
			mytoken = nextToken();
      return p;
    }
    else error(";", mytoken);
  }
  else if (mytoken.id == KEYWORD_TK && mytoken.instance == "void" ) {  //First(label)
    p->n0 = nonterminal.fn_label();
    if (mytoken.id == OPERATOR_TK && mytoken.instance == ";") {
      p->token = mytoken;
			mytoken = nextToken();
      return p;
    }
    else error(";", mytoken);
  }
} 


Node* Nonterminal :: fn_in() {  //done
  //<in> -> getter Identifier
  if (VERBOSE) cout << "call fn_in()" << endl;

	Node* p = addNode("in");
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "getter") {
    p->token = mytoken;
		mytoken = nextToken();
    if (mytoken.id == IDENTIFIER_TK) {    
      p->token = mytoken;
			mytoken = nextToken();
      return p;
    }
    else error(TOKENPRINTS[IDENTIFIER_TK], mytoken);
  }
  else error("getter", mytoken);
}


Node* Nonterminal :: fn_out() {  //done
  //<out> -> outter <expr>
  if (VERBOSE) cout << "call fn_out()" << endl;

	Node* p = addNode("out");
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "outter") {
    p->token = mytoken;
		mytoken = nextToken();
    p->n0 = nonterminal.fn_expr();
    return p;
  }
  else error("outter", mytoken);
}


Node* Nonterminal :: fn_if() {  //done
  //<if> -> if [ <expr> ] <RO> <expr> ] <stat>
  if (VERBOSE) cout << "call fn_if()" << endl;

	Node* p = addNode("if");
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "if") {
    p->token = mytoken;
		mytoken = nextToken();
    if (mytoken.id == OPERATOR_TK  && mytoken.instance == "[") {
      p->token = mytoken;
			mytoken = nextToken();
      p->n0 = nonterminal.fn_expr();
      p->n1 = nonterminal.fn_RO();
      p->n2 = nonterminal.fn_expr();
      if (mytoken.id == OPERATOR_TK && mytoken.instance == "]") {
        p->token = mytoken;
			  mytoken = nextToken();
        if (mytoken.id == KEYWORD_TK && mytoken.instance == "then") {
          p->token = mytoken;
			    mytoken = nextToken();
          p->n3 = nonterminal.fn_stat();
          return p;
        }
        else error("then", mytoken);
      }
      else error("]", mytoken);
    }
    else error("[", mytoken);
  }
  else error("if", mytoken);
}


Node* Nonterminal :: fn_loop() {  //done
  //<loop> -> loop [ <expr> <RO> <expr> ] <stat>
  if (VERBOSE) cout << "call fn_loop()" << endl;

	Node* p = addNode("loop"); 
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "loop") {
    p->token = mytoken;
		mytoken = nextToken();
    if (mytoken.id == OPERATOR_TK && mytoken.instance == "[") {
      p->token = mytoken;
			mytoken = nextToken();
      p->n0 = nonterminal.fn_expr();
      p->n1 = nonterminal.fn_RO();
      p->n2 = nonterminal.fn_expr();
      if (mytoken.id == OPERATOR_TK && mytoken.instance == "]") {
        p->token = mytoken;
			  mytoken = nextToken();
        p->n3 = nonterminal.fn_stat();
        return p;
      }
      else error("]", mytoken);
    }
    else error("[", mytoken);
  }
  else error("loop", mytoken);
}


Node* Nonterminal :: fn_assign() {  //done
  //<assign> -> assign Identifier := <expr>
  if (VERBOSE) cout << "call fn_assign()" << endl;

	Node* p = addNode("assign"); 
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "assign") {
    p->token = mytoken;
		mytoken = nextToken();
    if (mytoken.id == IDENTIFIER_TK) {
      p->token = mytoken;
			mytoken = nextToken();
      if (mytoken.id == OPERATOR_TK && mytoken.instance == ":=") {
        p->token = mytoken;
			  mytoken = nextToken();
        p->n0 = nonterminal.fn_expr();
        return p;
      }
      else error(":=", mytoken);
    }
    else error(TOKENPRINTS[IDENTIFIER_TK], mytoken);
  }
  else error("assign", mytoken);
}


Node* Nonterminal :: fn_goto() {  //done
  //<goto> -> proc Identifier
  if (VERBOSE) cout << "call fn_goto()" << endl;

	Node* p = addNode("goto"); 
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "proc") {
    p->token = mytoken;
		mytoken = nextToken();
    if (mytoken.id == IDENTIFIER_TK) {
      p->token = mytoken;
			mytoken = nextToken();
      return p;
    }
    else error(TOKENPRINTS[IDENTIFIER_TK], mytoken);
  }
  else error("proc", mytoken);
}


Node* Nonterminal :: fn_label() {  //done
  //<label> -> void Identifier
  if (VERBOSE) cout << "call fn_label()" << endl;

	Node* p = addNode("label"); 
  if (mytoken.id == KEYWORD_TK && mytoken.instance == "void") {
    p->token = mytoken;
		mytoken = nextToken();
    if (mytoken.id == IDENTIFIER_TK) {
      p->token = mytoken;
			mytoken = nextToken();
      return p;
    }
    else error(TOKENPRINTS[IDENTIFIER_TK], mytoken);
  }
  else error("void", mytoken);
}


Node* Nonterminal :: fn_expr() {  //done
  //<expr> -> <N> - <expr> | <N>
  if (VERBOSE) cout << "call fn_expr()" << endl;

	Node* p = addNode("expr"); 
  p->n0 = nonterminal.fn_N();
  if (mytoken.id == OPERATOR_TK && mytoken.instance == "-") {
    p->token = mytoken;
		mytoken = nextToken();
    p->n1 = nonterminal.fn_expr();
  }
  else {
    return p;
  }
}


Node* Nonterminal :: fn_N() {  //done
  //<N> -> <A> / <N> | <A> * <N> | <A>
  if (VERBOSE) cout << "call fn_N()" << endl;

	Node* p = addNode("N"); 
  p->n0 = nonterminal.fn_A();
  if (mytoken.id == OPERATOR_TK && mytoken.instance == "/") {
    p->token = mytoken;
		mytoken = nextToken();
    p->n1 = nonterminal.fn_N();
  }
  else if (mytoken.id == OPERATOR_TK && mytoken.instance == "*") {
    p->token = mytoken;
		mytoken = nextToken();
    p->n1 = nonterminal.fn_N();
  }
  else {
    return p;
  }
}


Node* Nonterminal :: fn_A() {  //done
  //<A> -> <M> + <A> | <M>
  if (VERBOSE) cout << "call fn_A()" << endl;

	Node* p = addNode("A"); 
  p->n0 = nonterminal.fn_M();
  if (mytoken.id == OPERATOR_TK && mytoken.instance == "+") {
    p->token = mytoken;
		mytoken = nextToken();
    p->n1 = nonterminal.fn_A();
    return p;
  }
  else {
    return p;
  }
}


Node* Nonterminal :: fn_M() {  //done
  //<M> -> * <M> | <R>
  if (VERBOSE) cout << "call fn_M()" << endl;

	Node* p = addNode("M"); 
  if (mytoken.id == OPERATOR_TK && mytoken.instance == "*") {
    p->token = mytoken;
		mytoken = nextToken();
    p->n0 = nonterminal.fn_M();
    return p;
  }
  else {
    p->n0 = nonterminal.fn_R();
    return p;
  }
}


Node* Nonterminal :: fn_R() {  //done
  //<R> -> ( <expr> ) | Identifier | Integer
  if (VERBOSE) cout << "call fn_R()" << endl;

	Node* p = addNode("R"); 
  if (mytoken.id == OPERATOR_TK && mytoken.instance == "(") {
    p->token = mytoken;
		mytoken = nextToken();
    p->n0 = nonterminal.fn_expr();
    if (mytoken.id == OPERATOR_TK && mytoken.instance == ")") {
      p->token = mytoken;
			mytoken = nextToken();
      return p;
    }
  }
  else if (mytoken.id == IDENTIFIER_TK) {
    p->token = mytoken;
		mytoken = nextToken();
    return p;
  }
  else if (mytoken.id == INTEGER_TK) {
    p->token = mytoken;
		mytoken = nextToken();
    return p;
  }
}


Node* Nonterminal :: fn_RO() {  //done
  //<RO> -> => | =< | == | [ == ] | %
  if (VERBOSE) cout << "call fn_RO()" << endl;

	Node* p = addNode("RO"); 
  if (mytoken.id == OPERATOR_TK && mytoken.instance == "=>") {
    p->token = mytoken;
		mytoken = nextToken();
    return p;
  }
  else if (mytoken.id == OPERATOR_TK && mytoken.instance == "=<") {
    p->token = mytoken;
		mytoken = nextToken();
    return p;
  }
  else if (mytoken.id == OPERATOR_TK && mytoken.instance == "==") {
    p->token = mytoken;
		mytoken = nextToken();
    return p;
  }
  else if (mytoken.id == OPERATOR_TK && mytoken.instance == "[" ) {
    p->token = mytoken;
		mytoken = nextToken();
    if (mytoken.id == OPERATOR_TK && mytoken.instance == "==") {
      p->token = mytoken;
			mytoken = nextToken();
      if (mytoken.id == OPERATOR_TK && mytoken.instance == "]") {
        p->token = mytoken;
			  mytoken = nextToken();
        return p;
      }
      else error("]", mytoken);
    }
    else error("==", mytoken);
  }
  else if (mytoken.id == OPERATOR_TK && mytoken.instance == "%") {
    p->token = mytoken;
		mytoken = nextToken();
    return p;
  }
  else error(TOKENPRINTS[OPERATOR_TK], mytoken);
}
