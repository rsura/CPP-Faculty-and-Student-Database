#ifndef ROLLBACK_H
#define ROLLBACK_H
#include <iostream>
#include <exception>

using namespace std;

template <class T>
class Rollback{
    public:
        Rollback();
        Rollback(int maxSize);
        ~Rollback();

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
Rollback<T>::Rollback(){
    mSize = 25;
    top = -1;
    changesForUndo = new T[mSize];
}

template <class T>
Rollback<T>::Rollback(int maxSize){
    mSize = maxSize;
    top = -1;
    changesForUndo = new T[mSize];
}

template <class T>
Rollback<T>::~Rollback(){
    delete [] changesForUndo;
}

template <class T>
void Rollback<T>::push(T data){
    if (!isFull()) {
        changesForUndo[++top] = data;
        return;
    }
    for (int i = 0; i < mSize - 1; ++i) {
        changesForUndo[i] = changesForUndo[i+1];
    }
    changesForUndo[top] = data;
}

template <class T>
T Rollback<T>::pop(){
    if(isEmpty()){
        throw runtime_error("ERROR: Can't rollback any more changes, because the limit of the rollback stack's saved changes has been reached.");
    }
    return changesForUndo[top--];
}

template <class T>
T* Rollback<T>::peek(){
    if(isEmpty()){
        throw runtime_error("ERROR: Rollback stack is empty!");
    }
    return &(changesForUndo[top]);
}

template <class T>
bool Rollback<T>::isEmpty(){
    return (top == -1);
}

template <class T>
bool Rollback<T>::isFull(){
    return (top == mSize - 1);
}

template <class T>
int Rollback<T>::getSize(){
    return (top + 1);
}

#endif