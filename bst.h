/**
 * Header and Implementation File: bst.h
 *
 * Full Name: Rahul Sura
 * Student ID: 2371308
 * Chapman email: sura@chapman.edu
 * Course: CPSC 350-03
 * Assignment: Assignment 6
 */

#ifndef BST_H // header guards
#define BST_H
#include <iostream>
#include "GenLinkedList.h"

using namespace std;

template<typename T> // template class because you can make list nodes of different types. However, it won't always properly work with T of pointer type
class TreeNode{
    public:
        TreeNode(); // default constructor - shouldn't be used in general but is there in case
        TreeNode(T key);
        ~TreeNode();

        T key; // key = data
        TreeNode<T> *left;
        TreeNode<T> *right;
};

/**
 * Default constructor - creates an empty tree node
 */
template <class T>
TreeNode<T>::TreeNode(){
    left = NULL;
    right = NULL;
    key = NULL;
}

/**
 * Overloaded constructor - creates a new tree node with the provided data
 * @param the data to be added into the tree
 */
template <class T>
TreeNode<T>::TreeNode(T k){
    left = NULL;
    right = NULL;
    key = k;
}

/**
 * Destructor
 */
template <class T>
TreeNode<T>::~TreeNode(){
    // nulls out the node's left and right pointers and deletes them, so that it's separated before deletion
    left = NULL;
    delete left;
    right = NULL;
    delete right;
}

// -------------------------------------BST-------------------------------------

template <class T> // template class because you can make list nodes of different types. However, it won't always properly work with T of pointer type
class BST{
    public:
        BST();
        virtual ~BST();
        void insert(T value);
        bool contains(T value); // search
        T* find(T value);
        bool deleteNode(T k);
        bool isEmpty();
        T* getMin();
        T* getMax();
        void printNodes();
        GenLinkedList<T*>* getPreOrderNodes();
    private:
         // helper functions
        void recDelete(TreeNode<T> *node);
        void recPrint(TreeNode<T> *node);
        void recPreOrderNodes(TreeNode<T> *node);
        TreeNode<T> *getSuccessor(TreeNode<T> *d); //d represents the node we are going to delete

        GenLinkedList<T*> *nodesInPreOrder;
        TreeNode<T> *root;
};

/**
 * Default constructor - creates an empty BST
 */
template <class T>
BST<T>::BST(){
    root = NULL;
    nodesInPreOrder = new GenLinkedList<T*>;
}

/**
 * Destructor
 */
template <class T>
BST<T>::~BST(){
    recDelete(root);
    root = NULL; // nulls out the root, in case it's not nulled out already, to indicate the tree is empty
    delete root;
    delete nodesInPreOrder;
}

/**
 * Helper function - recursively deletes the BST in postorder from a certain node,
 * but used for the destructor to delete the whole tree
 *
 * @param the starting node of the tree that needs to be deleted from
 */
template <class T>
void BST<T>::recDelete(TreeNode<T> *node){ // post order delete, so that no treenodes are orphaned
    if (node == NULL) {
        return;
    }
    if (node->left != NULL) {
        recDelete(node->left);
    }
    if (node->right != NULL) {
        recDelete(node->right);
    }
    delete node;
}

/**
 * Helper function - recursively prints the nodes of the BST from a certain node inorder,
 * but used by the printNodes() method to print all the nodes of the tree
 *
 * @param the node of the tree that needs to be printed from
 */
template <class T>
void BST<T>::recPrint(TreeNode<T> *node){ // inorder printing
    if(node == NULL){
        return;
    }
    recPrint(node->left);
    cout << node->key << endl;
    recPrint(node->right);
}

/**
 * Prints the nodes of the BST inorder, separated by line
 */
template <class T>
void BST<T>::printNodes(){
    recPrint(root); // printing inorder with the helper function
}

/**
 * Helper function - recursively adds constant references to values of the BST
 * from a certain node preorder, but used by the getPreOrderNodes() method to
 * get the values of the BST preorder into a linked list, so that it can be saved
 * and written back to the BST in the same way again.
 *
 * @param a linked list of constant pointers
 */
template <class T>
void BST<T>::recPreOrderNodes(TreeNode<T> *node){
    if(node == NULL){
        return;
    }
    nodesInPreOrder->insertBack(&(node->key));
    recPreOrderNodes(node->left);
    recPreOrderNodes(node->right);
}

/**
 * Gets the values of the BST preorder into a linked list, so that it can be saved
 * and written back to the BST in the same way again.
 *
 * @return a linked list of constant pointers
 */
template <class T>
GenLinkedList<T*>* BST<T>::getPreOrderNodes(){
    while (!nodesInPreOrder->isEmpty()) {
        nodesInPreOrder->removeFront();
    }
    recPreOrderNodes(root);
    return nodesInPreOrder;
}

/**
 * Checks if the tree is empty or not
 *
 * @return a bool representing if the tree is empty or not
 */
template <class T>
bool BST<T>::isEmpty(){
    return (root == NULL);
}

/**
 * Gets the minimum value from the tree
 *
 * @return a pointer to the minimum value of the tree
 */
template <class T>
T* BST<T>::getMin(){
    if(isEmpty()){
        return NULL;
    }
    TreeNode<T> *current = root;
    while(current->left != NULL){ // left most value is the smallest
        current = current->left;
    }
    return &(current->key);
}

/**
 * Gets the maximum value from the tree
 *
 * @return a pointer to the maximum value of the tree
 */
template <class T>
T* BST<T>::getMax(){
    if(isEmpty()){
        return NULL;
    }
    TreeNode<T> *current = root;
    while(current->right != NULL){ // right most value is the smallest
        current = current->right;
    }
    return &(current->key);
}

/**
 * Inserts a new node with the provided value
 *
 * @param value to be inserted
 */
template<class T>
void BST<T>::insert(T value){
    TreeNode<T> *node = new TreeNode<T>(value);
    if(isEmpty()){
        root = node;
        return;
    }
    TreeNode<T> *current = root;
    TreeNode<T> *parent = NULL;
    while(true){
        parent = current;
        if(value < current->key){
            // go left
            current = current->left;
            if(current == NULL){
                //we found the insertion point
                parent->left = node;
                break;
            }
        } else {
            // go right
            current = current->right;
            if(current == NULL){
                //we found the insertion point
                parent->right = node;
                break;
            }
        }
    }
}

/**
 * Checks if the tree contains a certain value
 *
 * @param value to be checked in the tree
 * @return a bool representing if the tree contains the value
 */
template<class T>
bool BST<T>::contains(T value){
    if(isEmpty()){
        return false;
    }

    TreeNode<T> *current = root; // tree node pointer to a possible value
    while(current->key != value){
        if(value < current->key){
            current = current->left;
        } else {
            current = current->right;
        }

        if(current == NULL){
            return false;
        }
    }

    return true;
}

/**
 * Checks if the tree contains a certain value and returns a pointer to the value
 * if found. Returns NULL if not found
 *
 * @param value to be found in the tree
 * @return a pointer to the found value of the tree. Returns NULL if value not found
 */
template<class T>
T* BST<T>::find(T value){
    if (!contains(value)) { // if tree doesn't have the value, returns null
        return NULL;
    }

    TreeNode<T> *current = root;
    while(current->key != value){
        if(value < current->key){
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return &(current->key); // reference to the key of the treenode
}

/**
 * Deletes a node, given a certain value
 *
 * @param value to be deleted in the tree
 * @return a bool representing if the node was successfully deleted or not.
 */
template <class T>
bool BST<T>::deleteNode(T k){
    if(isEmpty()){
        return false;
    }
    TreeNode<T> *current = root;
    TreeNode<T> *parent = root;
    bool isLeft = true;

    while(current->key != k){
        parent = current;
        if(k < current->key){
            isLeft = true;
            current = current->left;
        } else {
            isLeft = false;
            current = current->right;
        }
        if(current == NULL){
            return false;
        }
    }

    //we cound the node/value, now let's proceed to delete
    /* no children, node to be deleted is a leaf */
    if(current->left == NULL && current->right == NULL){
        if(current == root){
            root = NULL; // now it's an empty tree
        } else if(isLeft){
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
    } else if (current->right == NULL){
        // node to delete has a left child (no right)
        if (current == root) {
            root = current->left;
        } else if(isLeft){
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }

    } else if (current->left == NULL){
        // node to delete has a right child (no left)
        if (current == root) {
            root = current->right;
        } else if(isLeft){
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }
    } else {
        //node to be deleted has two children
        TreeNode<T> *successor = getSuccessor(current);
        if(current == root){
            root = successor;
        } else if (isLeft){
            parent->left = successor;
        } else {
            parent->right = successor;
        }
        successor->left = current->left;
        current->left = NULL;
        current->right = NULL;
    }
    delete current;
    return true;
}

/**
 * Helper function - gets the TreeNode pointer that has the nearest value to
 * the right of the passed in node
 *
 * @param a TreeNode pointer to find the successor of
 * @return a TreeNode pointer to representing the successor
 */
template <class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d){
    TreeNode<T> *sp /*(successor's parent)*/ = d;
    TreeNode<T> *successor = d;
    TreeNode<T> *current = d->right;

    while(current != NULL){
        sp = successor;
        successor = current;
        current = current->left;

    }

    // we found successor, but we need to check if the successor is a descendant of the right child
    if(successor != d->right){
        sp->left = successor->right;
        successor->right = d->right;
    }
    return successor;
}

#endif