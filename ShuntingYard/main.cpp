#include <iostream>
#include <cstring>
#include "treenode.h"
using namespace std;

/*
File: main file 
Name: Ethan Lynes
Overview: Take a mathematical ex and translate it to post fix notation. Take the postfix and create an ex tree. Allow the user to output the ex as infix, prefix, or postfix notation.
*/

// node struct
// character data, and a next link
// every node has an int to represent precedence
struct Node {
  char data;
  int prec;
  Node* next;
  tNode* tnode;
};


/* precedence
Power: 3
Divide: 2
Multiply: 2
Subtract: 1
Add: 1
*/
// prototypes
void push(Node* &top, char data, tNode* tnode);
void pop(Node* &top);
char peek(Node* top);
bool isEmpty(Node* top);
void display(Node* top);
void displayQueue(Node* front);
void toPostfix(Node* top, char exp[], Node* &front, Node* &tail);
void enqueue(Node* &front, Node* &tail, char data);
char dequeue(Node* &front, Node* &tail);

// main function
int main() {
   
  // input loop
  bool keep_going = true;
  while (keep_going) {

    // key pointers
    Node* top = NULL;
    Node* front = NULL;
    Node* tail = NULL;
    
    // take input (expression)
    cout << "enter an expression" << endl;
    char exp[100];
    cin.get(exp,100);
    cin.get();

    // remove spaces
    int count = 0;
    for (int i = 0; i < strlen(exp); i++) {
      if (exp[i] != ' ') {
        exp[count++] = exp[i];
      }
    }
    exp[count] = '\0';

    // translate to postfix notation
    toPostfix(top,exp,front,tail);

    // create expression tree

    cout << "front's data: " << endl;
    while (front != NULL) {
      if (front->data >= 48 && front->data <= 57) {
        // operand
	tNode* temp = new tNode(front->data);
	push(top, temp->data, temp);
      } else {
        // operator
	tNode* temp = new tNode(front->data);
	temp->right = top->tnode;
	pop(top);
	temp->left = top->tnode;
	pop(top);
	push(top, temp->data, temp);
      }
      front = front->next;
    }
    cout << "top's data: " << top->data << endl;
    cout << "top's left: " << top->tnode->left->data << endl;
    cout << "top's right: " << top->tnode->right->data << endl;
    cout << "top's right's right: " << top->tnode->right->right->data << endl;
    cout << "top's left's left: " << top->tnode->left->left->data << endl;
    display(top);

    // ask user whether to keep going
    cout << "do you want to keep going? ";
    char input[5] = "yes";
    cin.get(input,5);
    cin.get();
    if (input[0] == 'n') {
      keep_going = false;
    }
  }
  return 0;
}

// convert expression to postfix
void toPostfix(Node* top, char exp[], Node* &front, Node* &tail) {
  
  // temp strings
  int length = strlen(exp);

  //int count = 0;
  //char output[length];

  // go through input
  // while there are characters to be read
  for (int i = 0; i < length; i++) {
    // if the input is 0 - 9
    if ((exp[i] >= 48 && exp[i] <= 57) || (exp[i] >= 97 && exp[i] <= 122)) {

      //output[count] = exp[i];
      //count++;

      enqueue(front, tail, exp[i]);

    } else if (exp[i] == '-' || exp[i] == '+' || exp[i] == '*' || exp[i] == '/' || exp[i] == '^') {
      // char is an operator

      // checks first if the stack is empty
      // if so, add op to stack
      if (isEmpty(top)) {

        // if the stack is empty, push data to stack
        push(top, exp[i], NULL);

      } else {
        // not empty

        // assign a precedence to the current char
        int prec = 0;
        if (exp[i] == '-' || exp[i] == '+') {
          prec = 1;
        } else if (exp[i] == '/' || exp[i] == '*') {
          prec = 2;
        } else if (exp[i] == '^') {
          prec = 3;
        }

        // compare precedence between the current char and the top of the stack 

        //if the prec of top is greater or equal to current char, pop off stack
        while (top != NULL && top->prec >= prec && top->data != '(') {

          //output[count] = peek(top);
          //count++;

          enqueue(front, tail, peek(top));
          pop(top);
        }

        // otherwise, push to top
        push(top, exp[i], NULL);
      }
    } else if (exp[i] == '(') {

      // if the current char is a left parent. then push to stack
      push(top, exp[i], NULL);

    } else if (exp[i] == ')') {
      // if current char is right par., pop stack until it finds a left one

      while (top->data != '(') {

        //output[count] = peek(top);
        //count++;

        enqueue(front, tail, peek(top));
        pop(top);
      }
      // once it finds the left par., discard both par.
      if (top->data == '(') {

        pop(top);
        push(top, exp[i], NULL);
        pop(top);

      }
    }
  }

  while (!isEmpty(top)) {

    //output[count] = peek(top);
    //count++;

    enqueue(front, tail, peek(top));
    pop(top);
  }

  //output[count] = '\0';
  //cout << output << endl;

  displayQueue(front);
}

// push data onto the stack
void push(Node* &top, char data, tNode* tnode) {

  // create node temp and allocate it to memory
  Node* temp;
  temp = new Node;
  if (tnode == NULL) {
    // assign precedence based on data
    if (data == '-' || data == '+') {
      temp->prec = 1;
    } else if (data == '/' || data == '*') {
      temp->prec = 2;
    } else if (data == '^') {
      temp->prec = 3;
    }
    // assign data into new node
    temp->data = data;
    // make temp point to top of stack
    temp->next = top;
    // make temp the top of stack
    top = temp;
    
  } else {
    // if you're pushing a tree node
    // push pointer to stack
    temp->data = data;
    temp->tnode = tnode;
    temp->next = top;
    top = temp;
  }
}

// 'pop' or remove the node at the top of stack
void pop(Node* &top) {
  Node* temp;

  // check for stack underflow
  if (top == NULL) {
    cout << "stack underflow" << endl;
    return;
  }
  // make temp the top node
  temp = top;

  // make top the next node (below)
  top = top->next;

  // destroy connection between 
  temp->next = NULL;

  delete temp;
}

// 'peek' at the top of stack
// returns the data of the top node
char peek(Node* top) {
  if (!isEmpty(top)) {
    return top->data;
  } else {
    cout << "stack is empty" << endl;
    return 'e';
  }
}

// check if the stack is empty
// returns true if empty, false otherwise
bool isEmpty(Node* top) {
  if (top == NULL) {
    return true;
  } else {
    return false;
  }
}

// display the entire stack to the console
void display(Node* top) {

  // check for stack underflow
  if (top == NULL) {
    cout << "stack underflow" << endl;
  } else {
    // init temp to top
    Node* temp = top;
    cout << "stack:" << endl;
    // go through stack and print each node's data
    while (temp != NULL) {
      // print node data
      //cout << temp->data << " ";

      // if it has a tnode, print it
      if (temp->tnode != NULL) {
	cout << temp->tnode << " ";
      }
      
      // assign temp to it's next
      temp = temp->next;

    }
    cout << endl;
  }
}

// display the entire queue to the console
void displayQueue(Node* front) {

  // check for stack underflow
  if (front == NULL) {
    cout << "queue is empty" << endl;
  } else {
    // init temp to top
    Node* temp = front;
    
    //go through stack and print each node's data
    while (temp != NULL) {
      //print node data
      cout << temp->data;
      //assign temp to it's next
      temp = temp->next;

    }
    cout << endl;
  }
}

// add data to a queue
void enqueue(Node* &front, Node* &tail, char data) {

  if (tail == NULL) {
    // if tail is null, create a new node
    // initialize it to both tail and head
    tail = new Node;
    tail->data = data;
    front = tail;
  } else {
    // not empty
    // create a new node behind tail
    // make tail new node
    tail->next = new Node;
    tail = tail->next;
    tail->data = data;
    tail->next = NULL;
  }
}

// dequeue data from queue
char dequeue(Node* &front, Node* &tail) {

  
  Node* temp = front;
  front = front->next;

  if (front == NULL) {
    tail = NULL;
  }

  char data = temp->data;
  delete temp;
  return data;
}
