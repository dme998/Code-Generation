#ifndef PTREE_H
#define PTREE_H
#include <iostream>
#include <string>

using std::cout;
using std::endl;

class Node {
  public:
    std::string value;  //data string stored in node
    Node* left;
    Node* right;

    //constructor
    Node() {
      value = "";
      left = NULL;
      right = NULL;
    }
    Node(std::string s) {
      value = s;
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
