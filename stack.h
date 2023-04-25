#include <iostream>
using namespace std;

// Define the default capacity of the stack
#define SIZE 5

// A class to represent a stack
class Stack
{
    goodWithAction *arr;
    int top;
    int capacity;
 
public:
    Stack(int size = SIZE);         // constructor
    ~Stack();                       // destructor
 
    void push(goodWithAction);
    void pop();
    int peek();
    goodWithAction topItem();
 
    int size();
    bool isEmpty();
    bool isFull();
};
 
// Constructor to initialize the stack
Stack::Stack(int size)
{
    arr = new goodWithAction[size];
    capacity = size;
    top = -1;
}
 
// Destructor to free memory allocated to the stack
Stack::~Stack() {
    delete[] arr;
}
 
// Utility function to add an element `x` to the stack
void Stack::push(goodWithAction x)
{
    if (isFull())
    {
        cout << "Overflow\nProgram Terminated\n";
    }

    arr[++top] = x;
}
 
// Utility function to pop a top element from the stack
void Stack::pop()
{
    // check for stack underflow
    if (isEmpty())
    {
        cout << "Underflow\nProgram Terminated\n";
    }
 
    // decrease stack size by 1 and (optionally) return the popped element
    arr[top--].good.id;
}
 
// Utility function to return the top element of the stack
int Stack::peek()
{
    if (!isEmpty()) {
        return arr[top].good.id;
    } else {
        return -1;
    }
}

// Utility function to return the top element of the stack
goodWithAction Stack::topItem()
{
    if (!isEmpty()) {
        return arr[top];
    }
}
 
// Utility function to return the size of the stack
int Stack::size() {
    return top + 1;
}
 
// Utility function to check if the stack is empty or not
bool Stack::isEmpty() {
    return top == -1;               // or return size() == 0;
}
 
// Utility function to check if the stack is full or not
bool Stack::isFull() {
    return top == capacity - 1;     // or return size() == capacity;
}