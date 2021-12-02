/**
 * Header and Implementation File: Rollback.h
 *
 * Full Name: Rahul Sura
 * Student ID: 2371308
 * Chapman email: sura@chapman.edu
 * Course: CPSC 350-03
 * Assignment: Assignment 6
 */

#ifndef ROLLBACK_H // header guards
#define ROLLBACK_H
#include <iostream>
#include <exception>

using namespace std;

template <class T> // template class because you can make rollbacks of different types
class Rollback{ // functions like a stack but if it's full and more pushes happen, the bottom of the "stack" gets removed
    public:
        Rollback(); // default constructor - size of 25 undos
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


/**
 * Default constructor - creates an rollback with capacity of 25 undo operations
 */
template <class T>
Rollback<T>::Rollback(){
    mSize = 25;
    top = -1;
    changesForUndo = new T[mSize];
}

/**
 * Overloaded constructor - creates an rollback with capacity of specified number
 * of undo operations
 *
 * @param an int representing the rollback size. Throws an error if the rollback is zero or negative.
 */
template <class T>
Rollback<T>::Rollback(int maxSize){
    if (maxSize <= 0) {
        throw invalid_argument("ERROR: Cannot create a rollback of a negative or zero size");
    }
    mSize = maxSize;
    top = -1;
    changesForUndo = new T[mSize];
}

/**
 * Destructor
 */
template <class T>
Rollback<T>::~Rollback(){
    delete [] changesForUndo;
}

/**
 * Pushes the change to be undone onto the rollback. If the rollback is full,
 * the data from the bottom will be removed
 *
 * @param the change data
 */
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

/**
 * Pops the change to be undone from the top of the rollback
 *
 * @return the change data
 */
template <class T>
T Rollback<T>::pop(){
    if(isEmpty()){
        throw runtime_error("ERROR: Can't rollback any more changes, because the limit of the rollback stack's saved changes has been reached.");
    }
    return changesForUndo[top--];
}

/**
 * Shows the last change pushed to the rollback
 *
 * @return a pointer to the last change data
 */
template <class T>
T* Rollback<T>::peek(){
    if(isEmpty()){
        throw runtime_error("ERROR: Rollback stack is empty!");
    }
    return &(changesForUndo[top]);
}

/**
 * Checks if rollback is empty
 *
 * @return a bool representing if the rollback is empty or not
 */
template <class T>
bool Rollback<T>::isEmpty(){
    return (top == -1);
}

/**
 * Checks if rollback is full
 *
 * @return a bool representing if the rollback is full or not
 */
template <class T>
bool Rollback<T>::isFull(){
    return (top == mSize - 1);
}

/**
 * Gets the size of the number of rollbacks stored
 *
 * @return an int representing the number of rollback changes stored. Cannot exceed the specified limit in the constructor
 */
template <class T>
int Rollback<T>::getSize(){
    return (top + 1);
}

#endif