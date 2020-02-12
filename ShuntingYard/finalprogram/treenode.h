#include <iostream>
using namespace std;

/*
Ethan Lynes
2/12/20
File: tree node header file
*/

// tree node class
class tNode {
 public:
  // constructor and destructor
  tNode(char newdata);
  ~tNode();
  // data and right and left links
  char data;
  tNode* left;
  tNode* right;
};
