#ifndef PARSER_H
#define PARSER_H
#include "ptree.h"

ParseTree parser();

class Nonterminal {
  public:

    //constructor
    Nonterminal() {

    }
    
    //functions for each nonterminal
    void nt_program();
    void nt_block();
    void nt_vars();
    void nt_expr();
    void nt_N();
    void nt_A();
    void nt_M();
    void nt_R();
    void nt_stats();
    void nt_mStat();
    void nt_stat();
    void nt_in();
    void nt_out();
    void nt_if();
    void nt_loop();
    void nt_assign();
    void nt_RO();
    void nt_label();
    void nt_goto();
    
    void aux();  //check termination condition
};

#endif
