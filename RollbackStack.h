#ifndef ROLLBACKSTACK_H
#define ROLLBACKSTACK_H
#include <iostream>
#include <exception>

using namespace std;

template <class T>
class RollbackStack{
    public:
        RollbackStack();
        RollbackStack(int maxSize);
        ~RollbackStack();

        void push(T data);
        T pop();

        T* peek();
        bool isEmpty();
        bool isFull();
        int getSize();

    private:
        T *changesForUndo;
        int mSize;
        int top;
};

template <class T>
RollbackStack<T>::RollbackStack(){
    mSize = 25;
    top = -1;
    changesForUndo = new T[mSize];
}

template <class T>
RollbackStack<T>::RollbackStack(int maxSize){
    mSize = maxSize;
    top = -1;
    changesForUndo = new T[mSize];
}

template <class T>
RollbackStack<T>::~RollbackStack(){
    delete [] changesForUndo;
}

template <class T>
void RollbackStack<T>::push(T data){
    if (isFull()) {
        for (int i = 0; i < mSize - 1; i++) {
            changesForUndo[i] = changesForUndo[i+1];
        }
        changesForUndo[top] = data;
        return;
    }
    changesForUndo[++top] = data;
}

template <class T>
T RollbackStack<T>::pop(){
    if(isEmpty()){
        throw runtime_error("ERROR: Can't rollback any more changes, because the limit of the rollback stack's saved changes has been reached.");
    }
    return changesForUndo[top--];
}

template <class T>
T* RollbackStack<T>::peek(){
    if(isEmpty()){
        throw runtime_error("ERROR: Rollback stack is empty!");
    }
    return &(changesForUndo[top]);
}

template <class T>
bool RollbackStack<T>::isEmpty(){
    return (top == -1);
}

template <class T>
bool RollbackStack<T>::isFull(){
    return (top == mSize - 1);
}

template <class T>
int RollbackStack<T>::getSize(){
    return (top + 1);
}

#endif