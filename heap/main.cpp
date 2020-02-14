#include <iostream>
#include <cstring>

using namespace std;

/*
Ethan Lynes
2/14/20
Program: create a max heap given a list of numbers. Once done, the heap 
will remove each element in order and add them to an output.
The output would be from largest to smallest.
Also includes a way to visually represent the binary tree
*/

int main() {

  char numList[] = {"389 983 78 918 378 289 12 7 83"};

  int heap[101];
  for (int i = 0; i < strlen(numList); i++) {
    if (numList[i] != 32) {
      cout << numList[i];
      
    } else {
      cout << endl;
      break;
    }
  }
  cout << "yeet" << endl;
  return 0;
}
