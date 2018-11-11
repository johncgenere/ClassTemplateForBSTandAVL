/*
  Author: John Genere
*/

#ifndef TREES_H
#define TREES_H

template<class Type>
class BST{
public:
  BST();
  BST(const BST &rhs);
  BST(BST && rhs);
  ~BST();

  const Type& findMin() const;
  const Type& findMax() const;
  bool contains(const Type &x) const;
  bool isEmpty() const;
  void print() const;
  int height();
  int size();

  void makeEmpty();
  void insert(const Type &x);
  void insert(Type && x);
  void remove(const Type &x);

  BST& operator=(const BST &rhs);
  BST& operator=(BST && rhs);
  Type& operator[](const Type &x);
protected:
  struct Node{
    Type element;
    Node *left;
    Node *right;
    int height;

    Node(const Type &theElement, Node *lt, Node *rt, int h = 0):element(theElement), left(lt), right(rt), height(h){}
    Node(Type && theElement, Node *lt, Node *rt, int h = 0):element(std::move(theElement)), left(lt), right(rt), height(h){}
  };

  Node *root;

  Node* find(const Type &x, Node *&t);
  void insert(const Type &x, Node *&t);
  void insert(Type && x, Node *&t);
  void remove(const Type &x, Node *&t);
  Node* findMin(Node *t) const;
  Node* findMax(Node *t) const;
  bool contains(const Type &x, Node *t) const;
  void makeEmpty(Node *&t);
  void print(Node *t) const;
  Node* clone(Node *t) const;
  int height(Node *t) const;
  int size(Node*t) const;
};

template <class Type>
class AVL: public BST<Type>{
public:
  void insert(const Type &x);
  void remove(const Type &x);
private:
  void AVL_insert(const Type &x, typename BST<Type>::Node *&t);
  void balance(typename BST<Type>::Node *&t);
  void rotateWithLeftChild(typename BST<Type>::Node *&k2);
  void rotateWithRightChild(typename BST<Type>::Node *&k1);
  void doubleWithLeftChild(typename BST<Type>::Node *&k3);
  void doubleWithRightChild(typename BST<Type>::Node *&k3);
  void AVL_remove(const Type &x, typename BST<Type>::Node *&t);
  int height(typename BST<Type>::Node *t) const;
  int max(int lhs, int rhs) const;
};

#include "trees.cpp"
#endif
