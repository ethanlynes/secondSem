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
void infix(tNode* tree);
void prefix(tNode* tree);
void postfix(tNode* tree);

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
    cout << "Enter an expression: ";
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
    cout << "Successfully created expression tree." << endl;    

    // choose between infix, prefix, and postfix
    cout << "Do you want to output infix, prefix, or postfix? ";
    char choice[10];
    cin.get(choice,10);
    cin.get();

    // compare the input to each possible notation
    // execute functions accordingly
    cout << "Output: ";
    if (strcmp(choice,"infix") == 0) {
      infix(top->tnode);
    } else if (strcmp(choice,"prefix") == 0) {
      prefix(top->tnode);
    } else if (strcmp(choice,"postfix") == 0) {
      postfix(top->tnode);
    } else {
      cout << "You didn't choose one of the options." << endl;
    }
    cout << endl;

    // ask user whether to keep going
    cout << "Do you want to keep going? ";
    char input[5];
    cin.get(input,5);
    cin.get();
    // if input starts with an n, end program
    if (input[0] == 'n') {
      keep_going = false;
    } else {
      cout << endl;
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
      // add to output queue
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

	
        // if the prec of top (of stack) is greater or equal to
	// current char being evaluated, pop off stack
	// adds edge case for powers, if it's a power, push to stack without popping
	if (prec < 3) {
	  while (top != NULL && top->prec >= prec && top->data != '(') {
	    enqueue(front, tail, peek(top));
	    pop(top);
	  }
	}
        // otherwise, push to stack
        push(top, exp[i], NULL);
      }
    } else if (exp[i] == '(') {

      // if the current char is a left parentheses then push to stack
      push(top, exp[i], NULL);

    } else if (exp[i] == ')') {
      // if current char is right parentheses, pop stack until it finds a left one

      while (top->data != '(') {

	// add to output queue, pop from stack
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

  // push anything else still on the stack onto the output queue
  while (!isEmpty(top)) {

    enqueue(front, tail, peek(top));
    pop(top);
  }
}

// push data onto the stack
void push(Node* &top, char data, tNode* tnode) {

  // create node temp and allocate it to memory
  Node* temp;
  temp = new Node;

  // case if you're adding a normal char to stack
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

    // case if you're adding a tree node to stack  
  } else {
    // if you're pushing a tree node
    // init data and pointer onto stack
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

  // free temp from memory
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
// primarily used for debugging, not used in main sequence
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
      //cout << temp->data << endl;

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
// used for debuggig, not used in main sequence
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

// add data to back of the queue
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

// dequeue data from front of queue
char dequeue(Node* &front, Node* &tail) {

  // make a new temp node set to front
  // make front it's next
  Node* temp = front;
  front = front->next;

  // if front is then null, there is nothing in the list
  // make tail null
  if (front == NULL) {
    tail = NULL;
  }

  // delete temp and return it's data
  char data = temp->data;
  delete temp;
  return data;
}

// prints an expression in infix notation given a binary expression tree
void infix(tNode* tree) {
  // first checks if tree is empty
  if (tree != NULL) {
    if (tree->data == '-' || tree->data == '+' || tree->data == '*' || tree->data == '/' || tree->data == '^') {
      // if tree node data is an operator, you can then
      // determine that it is a subexpression and print a left parentheses
      cout << '(';
    }
    // go down left subtree
    infix(tree->left);
    // output data
    cout << tree->data;
    // go down right subtree
    infix(tree->right);
    
    if (tree->data == '-' || tree->data == '+' || tree->data == '*' || tree->data == '/' || tree->data == '^') {
      cout << ')';
    }
  }
}

// print expression tree as prefix notation
void prefix(tNode* tree) {

  // checks if tree is empty
  if (tree != NULL) {
    // output data first
    cout << tree->data;
    // then go down to the left subtree recursively
    prefix(tree->left);
    // then go down to right subtree
    prefix(tree->right);
  }
}

// print expression tree as postfix notation
void postfix(tNode* tree) {

  // checks if tree is empty
  if (tree != NULL) {
    // go down left subtree
    postfix(tree->left);
    // then right subtree
    postfix(tree->right);
    // then output data
    cout << tree->data;
  }
}
