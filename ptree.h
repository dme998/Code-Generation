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
#include <vector>
#include "token.h"
using std::cout;
using std::endl;

class Node {
    public:
    std::vector<token_t> leaves_v;
    std::string label; //string literal of the nonterminal function (e.g. "block", "mStat")
    int level;  //how deep the node is in the tree
     
    //child nodes
    Node* n0;
    Node* n1;
    Node* n2;
    Node* n3;
    
    //recursive function to traverse and print tree in preorder
    void print(Node* node, int level) {
      level++;
      if (node == NULL) {  return; }
      if (node->label != "program") {
        cout << endl; 
        for(int l = 0; l < level; l++) { 
          cout << "\t";
        }
      }
      cout << "<" << node->label << "> ";

      int sz = node->leaves_v.size();
      for(int i = 0; i < sz; i++) {
        cout << node->leaves_v.at(i).instance << " ";
      }
      print(node->n0, level);
      print(node->n1, level);
      print(node->n2, level);
      print(node->n3, level);
    }
};


#endif
