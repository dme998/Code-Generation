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

using std::cout;
using std::endl;

class Node {
  public:

    token_t token;
    std::string label; //string literal of the nonterminal function (e.g. "block", "mStat")
    int level;  //how deep the node is in the tree
    Node* left;
    Node* right;

    //constructor
    Node() {
      label = "?NT";
      left = NULL;
      right = NULL;
    }
    Node(std::string l) {
      label = l; //e.g. "block" or "mStat"
      left = NULL;
      right = NULL;
    }
};

class ParseTree {    
  public: 
    Node *root;
    int nodecount = 0;  //running total of nodes created
    
    //constructor
    ParseTree() {
      root = NULL;
    }

    void printLeftRight(Node *root, int column) {
      //TODO
    }

    void addNode(Node *newnode) {
      //TODO
    }
};

#endif