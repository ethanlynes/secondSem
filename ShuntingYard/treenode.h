#include <iostream>
using namespace std;

class tNode {
  public:
    tNode(char newdata);
    ~tNode();
    char data;
    tNode* left;
    tNode* right;
};