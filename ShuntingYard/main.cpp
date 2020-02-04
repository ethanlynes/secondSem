#include <iostream>
#include <cstring>
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
};


/* precedence
Power: 3
Divide: 2
Multiply: 2
Subtract: 1
Add: 1
*/
// prototypes
void push(Node* &top, char data);
void pop(Node* &top);
char peek(Node* top);
bool isEmpty(Node* top);
void display(Node* top);
void toPostfix(Node* top, char exp[]);
void enqueue(Node* &head, Node* &tail, char data);
Node* dequeue(Node* &head, Node* &tail);

// main function
int main() {
  // key pointers
  Node* top = NULL;
  Node* front = NULL;
  Node* tail = NULL;

  enqueue(front, tail, '1');
  enqueue(front, tail, '2');

  cout << "front: " << front->data << endl;
  cout << "tail: " << tail->data << endl;
  cout << dequeue(front, tail)->data << endl;
  /*
  bool keep_going = true;
  while (keep_going) {

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
    toPostfix(top,exp);

    // ask user whether to keep going
    cout << "do you want to keep going? ";
    char input[5] = "yes";
    cin.get(input,5);
    cin.get();
    if (input[0] == 'n') {
      keep_going = false;
    }
  }*/
  return 0;
}

// convert expression to postfix
void toPostfix(Node* top, char exp[]) {
  
  // temp strings
  int length = strlen(exp);
  int count = 0;
  char output[length];
  // go through input
  // while there are characters to be read
  for (int i = 0; i < length; i++) {
    // if the input is 0 - 9
    if ((exp[i] >= 48 && exp[i] <= 57) || (exp[i] >= 97 && exp[i] <= 122)) {
      output[count] = exp[i];
      count++;
    } else if (exp[i] == '-' || exp[i] == '+' || exp[i] == '*' || exp[i] == '/' || exp[i] == '^') {
      // char is an operator

      // checks first if the stack is empty
      // if so, add op to stack
      if (isEmpty(top)) {
        push(top, exp[i]);
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
          output[count] = peek(top);
          count++;
          pop(top);
        }
        // otherwise, push to top
        push(top, exp[i]);
      }
    } else if (exp[i] == '(') {
      // if the current char is a left parent. then push to stack
      push(top, exp[i]);
    } else if (exp[i] == ')') {
      // if current char is right par., pop stack until it finds a left one
      while (top->data != '(') {
        output[count] = peek(top);
        count++;
        pop(top);
      }
      // once it finds the left par., discard both par.
      if (top->data == '(') {
        pop(top);
        push(top, exp[i]);
        pop(top);
      }
    }
  }

  while (!isEmpty(top)) {
    output[count] = peek(top);
    count++;
    pop(top);
  }

  //display(top);
  output[count] = '\0';
  cout << output << endl;
}

// push data onto the stack
void push(Node* &top, char data) {

  // create node temp and allocate it to memory
  Node* temp;
  temp = new Node;

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
    
    //go through stack and print each node's data
    while (temp != NULL) {
      //print node data
      cout << temp->data << endl;
      //assign temp to it's next
      temp = temp->next;

    }
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
Node* dequeue(Node* &front, Node* &tail) {

  
  Node* temp = front;
  front = front->next;

  if (front == NULL) {
    tail = NULL;
  }

  Node* temp2 = temp;
  delete temp2;
  return temp;
}
