#include <iostream>
#include <cstring>
#include <cstdlib>

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

  int heap[201];

  
  char* tok = strtok(numList, " ");
  int count = 0;
  while (tok != NULL) {
    int temp = atoi(tok);
    heap[count++] = temp;
    tok = strtok(NULL, " ");
  }

  
  
  bool run = true;
  while (run) {
    char input[10];
    cout << "select an index to output" << endl;
    cin.get(input,10);
    cin.get();

    int index = atoi(input);
    cout << heap[index] << endl;
    
    char a[10];
    cout << "keep going? " << endl;
    cin.get(a,10);
    cin.get();
    
    if (a[0] == 'n') {
      run = false;
    }
  }
  
  return 0;
}

void heapify(int &arr[101], int i, int &count) {

  
}
