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
#include <string>
#include <vector>

extern std::vector<token_t> gtokens_v;
Node* parser();
token_t nextToken();
void error(std::string exp, token_t tk);
Node* addNode(std::string label);

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
    Node* fn_program(); //priority
    Node* fn_block(); //priority
    Node* fn_vars(); //priority
    Node* fn_expr();
    Node* fn_N();
    Node* fn_A();
    Node* fn_M();
    Node* fn_R();
    Node* fn_stats(); //priority
    Node* fn_mStat(); //priority
    Node* fn_stat(); //priority
    Node* fn_in(); //priority
    Node* fn_out();
    Node* fn_if();
    Node* fn_loop();
    Node* fn_assign();
    Node* fn_RO();
    Node* fn_label();
    Node* fn_goto();
};

#endif

