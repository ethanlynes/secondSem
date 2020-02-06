#include <iostream>
#include "treenode.h"
using namespace std;

tNode::tNode(char newdata) {
  data = newdata;
  left = NULL;
  right = NULL;
}

tNode::~tNode() {
  left = NULL;
  right = NULL;
}