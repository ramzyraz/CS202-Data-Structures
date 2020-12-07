#ifndef __BST_CPP
#define __BST_CPP
#include "bst.h"
#include <iostream>
#include <queue>
// HELPER FUNCTIONS HERE...
template <class T>
BST<T>::BST(){
	root = NULL;
}

template <class T>
BST<T>:: ~BST(){
    // your destructor code goes here
    node<T> *traverse = root;

    while (traverse != NULL){
        if (traverse->left != NULL)  traverse = traverse->left;
        if (traverse->right != NULL) traverse = traverse->right;
        delete traverse;
        traverse = NULL;
    }
}

template <class T>
int BST<T> :: height (node<T>* p){
   // your find height code goes here
   if (p == NULL){
    return 1;
   }
    return p->height;
}

template <class T>
int BST<T> :: balanceFactor(node<T>* p){
    // you can use this to find balance factor.
    if (p == NULL){
        return 0;
    }
    return height(p->right) - height(p->left);
}

template <class T>
void BST<T> :: fixHeight(node<T>* p){
    // use this function to fix height of a node after insertion or deletion.
    int h1 = height(p->left);
    int h2 = height(p->right);
    p->height = std::max(h1, h2) + 1;
}

// ROTATING HELPERS 
template <class T>
node<T>* BST<T> :: rotateleft(node<T>* p){
    // Rotate left code goes here.
    node<T> *m = p->right;
    p->right = m->left;
    m->left = p;

    fixHeight(p);
    fixHeight(m);
    p = m;
    return p;
}

template <class T>
node<T>* BST<T> :: rotateright(node<T>* p){
    // Rotate right code goes here
    node<T> *m = p->left;
    p->left = m->right;
    m->right = p;

    fixHeight(p);
    fixHeight(m);
    p = m;
    return p;
}

template <class T>
node<T>* BST<T> :: balance(node<T>* p){    
    // Balancing code goes here. You might need to find balance factor and call appropriate rotations.
    fixHeight(p);

    int bFact = balanceFactor(p);

    // If Right Left Case, then first it will rotate right the right of node p
    // And then when brackets end, it will rotate the node p left
    // If its Right Right Case, then it will simply rotate left
    // If its a Left Right Case, then it will first rotate left the left of note p
    // And then when brackets end, it will rotate the node p right
    // Else it will return p

    if (bFact > 1){
        if (balanceFactor(p->right) < 0){
            p->right = rotateright(p->right);
        }
        return rotateleft(p);
    }
    else if (bFact < -1){
        if (balanceFactor(p->left) > 0){
            p->left = rotateleft(p->left);
        }
        return rotateright(p);
    }
    return p;
}
// CLASS FUNCTIONS HERE
template <class T>
void BST<T> :: insert(string value,T k){
    root = insertHelper(value,k,root);
}
// insertion helpe  r
template <class T>
node<T>* BST<T> :: insertHelper(string value,T k, node<T> *p) { // note we need a helper because we need recursive calls
    // Insertion code goes here.
    if (p == NULL){
        p = new node<T>(k, value);
    }
    else if (k < p->key){
        p->left = insertHelper(value, k, p->left);
    }
    else if (k > p->key){
        p->right = insertHelper(value, k, p->right);
    }
    return balance(p);
}
template<class T>
node<T>* BST<T> :: search(T key){
    // Search code goes here.
    node<T> *checker = root;

    if (checker != NULL){
        while (checker != NULL){
            if (key < checker->key) {
                checker = checker->left;
            }
            else if (key > checker->key) {
                checker = checker->right;
            }
            else if (key == checker->key) {
                return checker;
            }
        }
    }
    else {
        return NULL;
    }
}
// DELETE HELPER FUNCTIONS
template<class T>
node<T>* BST<T> :: findmin(node<T> *p){
    // This function finds the min node of the tree.
    if(p == NULL)
        return NULL;
    else if(p->left == NULL)
        return p;
    else
        findmin(p->left);
}

template<class T>
node<T>* BST<T>::removemin(node<T>* p) {
    // This function recursively finds the min node and deletes it.
    if (p == NULL) {
        return NULL;
    }
    else if (p->left == NULL) {
        node<T> *t = p->right;
        delete t;
        return p->right;
    }
    else {
        p->left = removemin(p->left);
    }
    return balance(p);
}

template<class T>
void BST<T>::delete_node(T k){
    root = remove(root, k);
}

template<class T>
node<T>*  BST<T>::remove(node<T>* p, T k) // k key deletion from p tree
{
    // This function uses findmin and deletemin to delete arbitrary node in the tree.
    if (p == NULL) {
        return NULL;
    }
    else if (k < p->key) {
        p->left = remove(p->left, k);
    }
    else if (k > p->key) {
        p->right = remove(p->right, k);
    }
    else if (k == p->key){
        // Two Children
        if(p->right != NULL && p->left != NULL){
            node<T> *sucFind = findmin(p->right); //Finds successor
            sucFind->right = removemin(p->right); // Replaces it and deletes it
            sucFind->left = p->left; // Adjusts the left node
            return balance(sucFind); // Returns a balance Tree
        }
    // One Child
        else if(p->right == NULL) {
            node<T> *t = p->left;
            delete t;
            return p->left;
        }
        else if(p->left == NULL) {
            node<T> *t = p->right;
            delete t;
            return p->right;
        }
        // No Child
        else if (p->left == NULL && p->right == NULL)
        {
            delete p;
            p = NULL;
        }
    }
    return balance(p);
}
template<class T>
node<T>* BST<T>::getRoot(){
    return root;
}
#endif
