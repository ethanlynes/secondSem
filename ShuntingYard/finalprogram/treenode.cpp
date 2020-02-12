#include <iostream>
#include "treenode.h"
using namespace std;

/*
Ethan Lynes
2/12/20
File: binary expression tree node class file
*/

// constructor
// assign new data, init left and right pointers
tNode::tNode(char newdata) {
  data = newdata;
  left = NULL;
  right = NULL;
}

// destructor
// remove link to left and right pointers
tNode::~tNode() {
  left = NULL;
  right = NULL;
}
