/* Project:        Parser and Tree Builder (P2)
 * Filename:       parser.h
 * Description:    parses tokens according to specified BNF
 * Author:         Daniel Eggers <dme998@mail.umsl.edu>
 * Course:         Program Translation (CS4280-001)
 * Instructor:     Mark Hauschild
 * Date:           April 12, 2021 
 * All Files:      main.cpp parser.cpp parser.h driveScanner.cpp driveScanner.h 
                   scanner.cpp scanner.h ptree.h token.h
 */

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
