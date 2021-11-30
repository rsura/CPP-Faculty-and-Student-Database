/**
 * Header and Implementation File: GenLinkedList.h
 *
 * Full Name: Rahul Sura
 * Student ID: 2371308
 * Chapman email: sura@chapman.edu
 * Course: CPSC 350-03
 * Assignment: Assignment 6 (This file is from Assignment 4)
 */

#ifndef GENLINKEDLIST_H // header guards
#define GENLINKEDLIST_H

#include <iostream>
#include <exception>
#include <sstream>

using namespace std;

template<typename T> // template class because you can make list nodes of different types
class ListNode{
    public:
        ListNode(); // default constructor - shouldn't be used in general but is there in case
        ListNode(T d);
        ~ListNode();
        T data;
        ListNode<T> *prev;
        ListNode<T> *next;
};


/**
 * Default constructor - creates an empty list node
 */
template<typename T>
ListNode<T>::ListNode(){}

/**
 * Overloaded constructor - creates a new list node with the provided data
 * @param the data to be added into the listnode
 */
template<typename T>
ListNode<T>::ListNode(T d){
    data = d;
    next = NULL;
    prev = NULL;
}

/**
 * Destructor
 */
template<typename T>
ListNode<T>::~ListNode(){
    // nulls out the node's next and previous pointers and deletes them, so that it's separated before deletion
    next = NULL;
    delete next;
    prev = NULL;
    delete prev;
}

// --------------------------GenLinkedList--------------------------------------

template<typename T> // template class because you can make linked lists of different types
class GenLinkedList{
    public:
        GenLinkedList();
        ~GenLinkedList();
        void insertFront(T d);
        void insertBack(T d);
        void insertNode(T d, int pos);
        T removeFront();
        T removeBack();
        T removeNode(int pos); // removes and returns the node from a certain position
        int find(T value); // finds the position of a certain value
        void sort();
        void print();
        void printReverse();
        bool isEmpty();
        unsigned int getSize();
    private:
        ListNode<T> *front;
        ListNode<T> *back;
        unsigned int size; // size of dynamically resizable linked list
};

/**
 * Default constructor - Creates an empty linked list
 */
template<typename T>
GenLinkedList<T>::GenLinkedList(){
    size = 0;
    front = NULL;
    back = NULL;
}

/**
 * Destructor
 */
template<typename T>
GenLinkedList<T>::~GenLinkedList(){
    while (size > 1) { // deletes every node except the last node
        ListNode<T> *old = front;
        front = front->next;
        delete old;
        --size;
    }
    delete front; // deletes the final node in the list
    --size;
}

/**
 * Inserts a node into the front of the linked list
 *
 * @param data with the linked list's data type
 */
template<typename T>
void GenLinkedList<T>::insertFront(T d){
    ListNode<T> *node = new ListNode<T>(d);
    if (!isEmpty()) { // inserting if list contains data
        node->next = front;
        front->prev = node;
    } else { // inserting if list doesn't contain data
        back = node;
    }
    front = node; // reassigns front node
    ++size;
}

/**
 * Inserts a node into the end of the linked list
 *
 * @param data with the linked list's data type
 */
template<typename T>
void GenLinkedList<T>::insertBack(T d){
    ListNode<T> *node = new ListNode<T>(d);
    if (!isEmpty()) { // inserting if list contains data
        node->prev = back;
        back->next = node;
    } else { // inserting if list doesn't contain data
        front = node;
    }
    back = node; // reassigns back node
    ++size;
}

/**
 * Inserts a node at a specific position in the linked list
 *
 * @param data with the linked list's data type
 * @param int represeting the position of the node to be inserted at
 */
template<typename T>
void GenLinkedList<T>::insertNode(T d, int pos){
    if(pos < 0 || pos > getSize()){
        throw runtime_error("ERROR: Invalid list position!");
    }
    if(pos == 0){ // inserting at front
        insertFront(d);
        return;
    } else if(pos == getSize()){ // inserting at back
        insertBack(d);
        return;
    }
    ListNode<T> *node = new ListNode<T>(d);
    ListNode<T> *curr = front;
    for(int i = 0; i < pos; ++i){
        curr = curr->next;
    }
    curr->prev->next = node;
    node->next = curr;
    node->prev = curr->prev;
    curr->prev = node;
    ++size;
}

/**
 * Removes a node from the front of the linked list
 *
 * @return data from the deleted node with the linked list's data type
 */
template<typename T>
T GenLinkedList<T>::removeFront(){
    if(isEmpty()){ // error for deleting from and empty list
        throw runtime_error("ERROR: List is empty!");
    }
    ListNode<T> *temp = front;
    if(size == 1){ // deleting the only element in the list
        back = NULL;
    } else {
        front->next->prev = NULL;
    }
    front = front->next; // reassigns front pointer
    temp->next == NULL;
    T data = temp->data;
    --size;
    delete temp;
    return data;
}

/**
 * Removes a node from the end of the linked list
 *
 * @return data from the deleted node with the linked list's data type
 */
template<typename T>
T GenLinkedList<T>::removeBack(){
    if(isEmpty()){ // error for deleting from and empty list
        throw runtime_error("ERROR: List is empty!");
    }
    ListNode<T> *temp = back;
    if (size == 1) { // deleting the only element in the list
        front = NULL;
    } else {
        back->prev->next = NULL;
    }
    back = back->prev; // reassigns back pointer
    temp->prev == NULL;
    T data = temp->data;
    --size;
    delete temp;
    return data;
}

/**
 * Removes the node with the given value and returns the position in which the
 * data that was removed
 *
 * @param an int representing the position of the removed node
 * @return data with the linked list's data type (returns NULL if no value found at that position or position is invalid)
 */
template<typename T>
T GenLinkedList<T>::removeNode(int pos){
    if(isEmpty()){ // error for deleting from and empty list
        throw runtime_error("ERROR: List is empty!");
    }
    if(pos < 0 || pos >= getSize()){
        throw runtime_error("ERROR: Invalid list position!");
    }
    if(size == 1){
        // cout << "removing last element " << endl;
        return removeFront();
    }

    ListNode<T> *curr = front;
    int counter = 0;
    while (counter != pos) { // finds the node to be deleted
        curr = curr->next;
        ++counter;
    }

    if (curr != front && curr != back) { // if node is in the middle
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }

    if(curr == front){ // if the node is in the front
        front = curr->next;
        front->prev = NULL;
    }

    if(curr == back){ // if the node is in the back
        back = curr->prev;
        back->next = NULL;
    }

    curr->next = NULL; // reassignments
    curr->prev = NULL;
    --size;
    return curr->data;
}

/**
 * Finds the node with the given value and returns the position in which the
 * data that was found
 *
 * @param data with the linked list's data type
 * @return an int representing the position of the found node (returns -1 if
 * the data was not found in the linked list)
 */
template<typename T>
int GenLinkedList<T>::find(T value){
    int pos = -1;
    ListNode<T> *curr = front;

    while (curr != NULL) { // finds the position by traversal
        ++pos;
        if(curr->data == value){
            return pos;
        }
        curr = curr->next;
    }
    return -1;
}

/**
 * Sorts the linked list in ascending order (using the <= operator). If your
 * linked list is of a data type that's not primitive, please overload those operators
 * in your class.
 */
template<typename T>
void GenLinkedList<T>::sort(){
    int until = size;
    ListNode<T> *currSmallest = front;
    ListNode<T> *curr = front;
    for(int i = 0; i < size; ++i){
        for(int j = i; j < until; ++j){
            if (curr->data <= currSmallest->data) {
                currSmallest = curr;
            }
            curr = curr->next;
        }
        insertBack(removeNode(find(currSmallest->data)));
        curr = front;
        currSmallest = front;
    }
}

/**
 * Prints the linked list in order (not sorted order)
 */
template<typename T>
void GenLinkedList<T>::print(){
    if(size == 0){
        cout << "Empty list with no elements." << endl;
        return;
    }
    ListNode<T> *curr = front;
    ostringstream listString;
    while(curr->next != NULL){
        listString << curr->data << endl;
        curr = curr->next;
    }
    listString << curr->data;
    cout << listString.str() << endl;
}

/**
 * Prints the linked list in reverse order (not sorted order in reverse)
 */
template<typename T>
void GenLinkedList<T>::printReverse(){
    if(size == 0){
        cout << "Empty list with no elements." << endl;
        return;
    }
    ListNode<T> *curr = back;
    ostringstream listString;
    while(curr->prev != NULL){
        listString << curr->data << endl;
        curr = curr->prev;
    }
    listString << curr->data;
    cout << listString.str() << endl;
}

/**
 * Checks if the linked list is empty
 *
 * @return a boolean representing if the linked list is empty
 */
template<typename T>
bool GenLinkedList<T>::isEmpty(){
    return (size == 0);
}

/**
 * Finds the size of the linked list
 *
 * @return an unsigned int representing the size of the linked list
 */
template<typename T>
unsigned int GenLinkedList<T>::getSize(){
    return size;
}

#endif
