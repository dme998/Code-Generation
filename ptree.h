/* Project:        Parser and Tree Builder (P2)
 * Filename:       ptree.h
 * Description:    defines parse tree class and tree node class
 * Author:         Daniel Eggers <dme998@mail.umsl.edu>
 * Course:         Program Translation (CS4280-001)
 * Instructor:     Mark Hauschild
 * Date:           April 12, 2021 
 * All Files:      main.cpp parser.cpp parser.h driveScanner.cpp driveScanner.h 
                   scanner.cpp scanner.h ptree.h token.h
 */

#ifndef PTREE_H
#define PTREE_H
#include <iostream>
#include <string>
#include "token.h"

class Node {
    public:
    token_t token;
    std::string label; //string literal of the nonterminal function (e.g. "block", "mStat")
    int level;  //how deep the node is in the tree
    
    //child nodes
    Node* n0;
    Node* n1;
    Node* n2;
    Node* n3;
    
    //recursive function to traverse and print tree in preorder
    void print(Node* node, int level) {
      string line;
      for(int i = 0; i < 1; i++) {
        if (node == NULL) {
          return;
        }
        else {
          for(int counter = 0; counter < level; counter++) {
            line.append("  ");
          } 
          line.append(node->label + " ");
          std::cout << line << std::endl;
          print(node->n0, level++); 
          print(node->n1, level++); 
          print(node->n2, level++); 
          print(node->n3, level++); 
        }
      }
    }
    
};


#endif
