/*
  Author: John Genere
*/
#ifndef TREES_CPP
#define TREES_CPP

#include <iostream>
#include <utility>
#include "trees.h"

static const int ALLOWED_IMBALANCE = 1; // for AVL

// Initializes empty container
template<class Type>
BST<Type>::BST(){
  root = nullptr;
}

// copy constructor
template<class Type>
BST<Type>::BST(const BST &rhs):root(nullptr){
  root = clone(rhs.root);
}

// move constructor
template<class Type>
BST<Type>::BST(BST && rhs):root(std::move(rhs.root)){
  rhs.root = nullptr;
}

// empties tree
template<class Type>
BST<Type>::~BST(){
  makeEmpty();
}

// finds left most element
template<class Type>
const Type& BST<Type>::findMin() const{
  return findMin(root)->element;   // returns element at left most root
}

// finds right most element
template<class Type>
const Type& BST<Type>::findMax() const{
  return findMax(root)->element;   // returns element at right most root
}

// calls private function contains
template<class Type>
bool BST<Type>::contains(const Type &x) const{
  return contains(x, root);        // call to private function
}

// returns true if container is empty
template<class Type>
bool BST<Type>::isEmpty() const{
  if(root == nullptr)
    return true;
  else
    return false;
}

// calls print function from private
template<class Type>
void BST<Type>::print() const{
  print(root);                     // call to private function
}

// returns height of tree
template<class Type>
int BST<Type>::height(){
  return height(root);             // call to private function
}

// returns number of items in container
template<class Type>
int BST<Type>::size(){
  return size(root);               // call to private function
}

// calls recursive makeEmpty function from private
template<class Type>
void BST<Type>::makeEmpty(){
  makeEmpty(root);                 // call to private function
}

// calls copy insert function from private
template<class Type>
void BST<Type>::insert(const Type &x){
  insert(x, root);                 // call to private function
}

// calls move insert function from private
template<class Type>
void BST<Type>::insert(Type && x){
  insert(std::move(x), root);      // call to private function
}

// calls recursive remove function from private
template<class Type>
void BST<Type>::remove(const Type &x){
  remove(x, root);                 // call to private function
}

// copy assignment
template<class Type>
BST<Type>& BST<Type>::operator=(const BST<Type> &rhs){
  BST <Type> tmp = rhs;     // temp object gets rhs
  std::swap(*this, tmp);    // swap lhs object with tmp
  return *this;             // return
}

// move assignment
template<class Type>
BST<Type>& BST<Type>::operator=(BST<Type> && rhs){
  std::swap(root, rhs.root);    // swap roots
  return *this;                 // return
}

// subscript operator that returns the reference of an item
template<class Type>
Type& BST<Type>::operator[](const Type &x) {
  if(contains(x)){
    Node *tmp = find(x, root);   // tmp gets node that contains x
    return tmp->element;         // returns ref to element at node found with find()
  }
  else
    std::cout << "ILLEGAL INSTRUCTION--The item you entered is not in the tree.\n";
    /*
      Compiler will not allow such command, program ends when trying to
      return the reference of an element that is not on the tree

      This will give a warning since for the else statement there is no return
    */
}

// inserts x into null node iteratively
template<class Type>
void BST<Type>::insert(const Type &x, Node *&t){
  Node *current = t;
  Node *parent = nullptr;

  if(t == nullptr){
    t = new Node(x, nullptr, nullptr);   // creates node for empty node
    return;
  }

  while(current != nullptr){
    parent = current;
    if(x < current->element)   // go to left child
      current = current->left;
    else                    // go to right child
      current = current->right;
  }

  if(x < parent->element)
    parent->left = new Node(x, nullptr, nullptr);
  else
    parent->right = new Node(x, nullptr, nullptr);
}

// inserts x into null node recursively
template<class Type>
void BST<Type>::insert(Type && x, Node *&t){
  if(t == nullptr)    // no node, create one
    t = new Node(std::move(x), nullptr, nullptr);
  else if(x < t->element)   // go to left child
    insert(std::move(x), t->left);
  else if(t->element < x)   // go to right child
    insert(std::move(x), t->right);
  else
    ;    // x is a duplicate, so do nothing
}

// removes element from tree t
template<class Type>
void BST<Type>::remove(const Type &x, Node *&t){
  if(t == nullptr)
    return;   // no item found, do nothing
  if(x < t->element)
    remove(x, t->left);   // check in left child for x
  else if(t->element < x)
    remove(x, t->right);  // check in right child for x
  else if(t->left != nullptr && t->right != nullptr){  // two children
    t->element = findMin(t->right)->element;
    remove(t->element, t->right);   // remove right childs lowest element
  }
  else{
    Node *oldNode = t;
    t = (t->left != nullptr) ? t->left : t->right;
    delete oldNode;
  }
}

// finds left most node which is the min value
template<class Type>
typename BST<Type>::Node* BST<Type>::findMin(Node *t) const{
  if(t != nullptr){
    while (t->left != nullptr){
      t = t-> left;
    }
  }
  return t;
}

// finds right most node which is the max value
template<class Type>
typename BST<Type>::Node* BST<Type>::findMax(Node *t) const{
  if(t != nullptr){
    while(t->right != nullptr){
      t = t->right;
    }
  }
  return t;
}

// checks if x is in tree t recursively
template<class Type>
bool BST<Type>::contains(const Type &x, Node *t) const{
  if (t == nullptr)
    return false;     // x not in tree, do nothing
  else if(x < t->element)
    return contains(x, t->left);  // check for x in left child
  else if(t->element < x)
    return contains(x, t->right); // check for x in right child
  else
    return true;      // x is in the tree
}

// starting from root, recursively empties tree
template<class Type>
void BST<Type>::makeEmpty(Node *&t){
  if(t != nullptr){
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
  }
  t = nullptr;
}

// prints tree in ascending order
template<class Type>
void BST<Type>::print(Node *t) const{
  if(t != nullptr){
    if(t -> left != nullptr){
      print(t->left);
    }
    std::cout << t->element << std::endl;
    if(t->right != nullptr){
      print(t->right);
    }
  }
  else{
    std::cout << "The tree is empty" << std::endl;
  }
}

// make a copy of a tree to give to another tree
template<class Type>
typename BST<Type>::Node* BST<Type>::clone(Node *t) const{
  if(t == nullptr)
    return nullptr;
  else
    return new Node(t->element, clone(t->left), clone(t->right), t->height);
}

// returns height of tree
template<class Type>
int BST<Type>::height(Node *t) const{
  if(t == nullptr)
    return -1;
  else{
    int lHeight = height(t->left);
    int rHeight = height(t->right);

    if(lHeight > rHeight)
        return(lHeight + 1);
    else
        return(rHeight + 1);
  }
}

// returns number of items in tree
template<class Type>
int BST<Type>::size(Node *t) const{
  if(t == nullptr){
    return 0;
  }
  return (1 + size(t->left) + size(t->right));
}

// finds element x in tree
template<class Type>
typename BST<Type>::Node* BST<Type>::find(const Type &x, Node *&t){
  if(t == nullptr || t->element == x)
    return t;
  if(x < t->element)
    return find(x, t->left);
  if(t->element < x)
    return find(x, t->right);

  return t;
}

// inserts item in AVL tree
template<class Type>
void AVL<Type>::insert(const Type &x){
  AVL_insert(x, BST<Type>::root);
}

// inserts item x into tree t then balances tree
template<class Type>
void AVL<Type>::AVL_insert(const Type &x, typename BST<Type>::Node*&t){
  typename BST<Type>::Node *current = t;
  typename BST<Type>::Node *parent = nullptr;

  if(t == nullptr){
    t = new typename BST<Type>::Node(x, nullptr, nullptr);
    return;
  }

  while(current != nullptr){
    parent = current;
    if(x < current->element)
      current = current->left;
    else
      current = current->right;
  }

  if(x < parent->element)
    parent->left = new typename BST<Type>::Node(x, nullptr, nullptr);
  else
    parent->right = new typename BST<Type>::Node(x, nullptr, nullptr);

  balance(t);
}

// balances tree
template<class Type>
void AVL<Type>::balance(typename BST<Type>::Node *&t){
  if(t == nullptr){
    return;
  }
  if(height(t->left) - height(t->right) > ALLOWED_IMBALANCE){
    if(height(t->left->left) >= height(t->left->right))
      rotateWithLeftChild(t);
    else
      doubleWithLeftChild(t);
  }
  else if((height(t->right) - height(t->left)) > ALLOWED_IMBALANCE){
    if(height(t->right->right) >= height(t->right->left))
      rotateWithRightChild(t);
    else
      doubleWithRightChild(t);
  }
  t->height = max(height(t->left), height(t->right)) + 1;
}

// single rotation
template<class Type>
void AVL<Type>::rotateWithLeftChild(typename BST<Type>::Node *&k2){
  typename BST<Type>::Node *k1 = k2->left;   // tmp node given is left child
  k2->left = k1->right;                      // left child is right child of tmp
  k1->right = k2;                            // right child of tmp is now k2
  k2->height = max(height(k2->left), height(k2->right)) + 1;
  k1->height = max(height(k1->left), k2->height) + 1;

  k2 = k1;
}

// single rotation
template<class Type>
void AVL<Type>::rotateWithRightChild(typename BST<Type>::Node *&k1){
  typename BST<Type>::Node *k2 = k1->right;
  k1->right = k2->left;
  k2->left = k1;
  k1->height = max(height(k1->left), height(k1->right)) + 1;
  k2->height = max(height(k2->right), k1->height) + 1;

  k1 = k2;
}

// double rotation
template<class Type>
void AVL<Type>::doubleWithLeftChild(typename BST<Type>::Node *&k3){
  rotateWithRightChild(k3->left);
  rotateWithLeftChild(k3);
}

// double rotation
template<class Type>
void AVL<Type>::doubleWithRightChild(typename BST<Type>::Node *&k3){
  rotateWithLeftChild(k3->right);
  rotateWithRightChild(k3);
}

// removes item
template<class Type>
void AVL<Type>::remove(const Type &x){
  AVL_remove(x, BST<Type>::root);       // call to private function
}

// removes item x from tree t then balances tree
template<class Type>
void AVL<Type>::AVL_remove(const Type &x, typename BST<Type>::Node *&t){
  if(t == nullptr)
    return;   // no item found, do nothing
  if(x < t->element)
    AVL_remove(x, t->left);   // check in left child for x
  else if(t->element < x)
    AVL_remove(x, t->right);  // check in right child for x
  else if(t->left != nullptr && t->right != nullptr){  // two children
    t->element = BST<Type>::findMin(t->right)->element;
    AVL_remove(t->element, t->right);   // remove right childs lowest element
  }
  else{
    typename BST<Type>::Node *oldNode = t;
    t = (t->left != nullptr) ? t->left : t->right;
    delete oldNode;
  }

  balance(t);                // balances tree after removal
}

// returns height of the AVL tree
template<class Type>
int AVL<Type>::height(typename BST<Type>::Node *t) const{
    return t == nullptr ? -1 : t->height;
}

// returns max of values inside parameter
template<class Type>
int AVL<Type>::max(int lhs, int rhs) const{
  return lhs > rhs ? lhs : rhs;
}

#endif
