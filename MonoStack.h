#ifndef MONOSTACK_H
#define MONOSTACK_H

#include <iostream>
using namespace std;

// Template function to print the stack in matrix format
template <typename T>
class MonoStack
{
    private:
    T* arr;
    int top;
    int capacity;
    char order;

    public:
        MonoStack(int size, char o) : capacity(size), top(-1), order(o) {
            if(o != 'i' && o != 'd'){
                cout << "The Order has to be either 'i' for increasing or 'd' for decreasing" << endl;
                throw std::invalid_argument("Invalid order");
            }
            arr = new T[capacity];
        }

        ~MonoStack(){
            delete[] arr; //frees dynamically allocated memory
        }

        void push(T x){ //returns a new element onto the stack but keeping the inc/dec order
            if(isFull()){
                cout << "Stack is full " << endl;
                return;
            }

            if(order == 'i'){
                while(!isEmpty() && arr[top] > x){
                    top--;
                }
            } else {
                while(!isEmpty() && arr[top] < x){
                    top--;
                }
            }
            top++;
            arr[top] = x;
        }

        T pop() { //removes the top value of the stack and returns
            if (isEmpty()){
                cout << "Stack is empty" << endl;
                throw std::underflow_error("Stack is empty");
            }
            return arr[top--];
        }

        T peek() const { // peeking at the top but not return because we want to just see
            if(isEmpty()){
                cout << "Stack is empty" << endl;
                throw std::underflow_error("Stack is empty");
            }
            return arr[top];
        }

        bool isEmpty() const { //check if stack is empty
            return top == -1;
        }

        bool isFull() const { //check if stack is full
            return top == capacity - 1;
        }
};

#endif