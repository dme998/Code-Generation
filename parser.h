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

extern std::vector<token_t> gtokens_v;
ParseTree parser();
token_t nextToken();

class Nonterminal {
  public:

    //constructor
    Nonterminal() {
      
    }
    
    /* functions for each nonterminal
     * each fn creates exactly one tree node (or none if going into empty production)
     * syntactic TKs (e.g. begin, end) can be thrown away; all others (ops, IDs, numbers) are stored in the node.
     * every node has label consistent with the name of the function creating it
     */
    void fn_program(); //priority
    void fn_block(); //priority
    void fn_vars(); //priority
    void fn_expr();
    void fn_N();
    void fn_A();
    void fn_M();
    void fn_R();
    void fn_stats(); //priority
    void fn_mStat(); //priority
    void fn_stat(); //priority
    void fn_in(); //priority
    void fn_out();
    void fn_if();
    void fn_loop();
    void fn_assign();
    void fn_RO();
    void fn_label();
    void fn_goto();
};

#endif
