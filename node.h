#ifndef NODE_H
#define NODE_H
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

class BST {    
  public: 
    Node *root;
    int nodecount = 0;  //running total of nodes created
    
    //constructor
    BST() {
      root = NULL;
    }

    //print 2D sideways binary tree
    //column is number of spaces used to separate nodes when printing
    void printLeftRight(Node *root, int column) {
      if (root == NULL) { return; }
      column += 6;
      printLeftRight(root->right, column);
      cout << endl;
      
      for(int i=6; i<column; i++) {
        cout << " ";
      }
      cout << root->value << "\n";
      printLeftRight(root->left, column);
    }

    void addNode(Node *newnode) {
      cout << "addNode(" << newnode->value << ")" << endl;
      if (root == NULL) {
        root = newnode;
        nodecount++;
        cout << "Value added as root node. " << endl;
      }
      else {
        Node *temp = root;  //previous node
        
        //traverse tree until we can add the new node in appropriate place
        while(temp != NULL) {
          if (newnode->value == temp->value) {  
            //cout << "Value already exists." << endl;
            //cout << newnode->value << " == " << temp->value << endl;
            return;
          }
          //left
          else if ( (newnode->value < temp->value) && (temp->left == NULL) ) {
            temp->left = newnode;
            nodecount++;
            cout << "Added left node." << endl;
            break;
          }
          else if (newnode->value < temp->value) {
            temp = temp->left;
          }
          //right
          else if ( (newnode->value > temp->value) && (temp->right == NULL) ) {
            temp->right = newnode;
            nodecount++;
            cout << "Added right node." << nodecount << endl;
            break;
          }
          else {
            temp = temp->right;
          }
        }
      }
    }
};

#endif
