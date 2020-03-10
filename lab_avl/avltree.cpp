/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <cmath>
#include <iostream>

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* tmp = t->right->left;
    Node* tmp2 = t->right->right;
    t->right->left = t->left;
    t->right->right = tmp;
    t->left = t->right;
    t->right = tmp2;
    swap(t, t->left);
    t->height = getHeight(t);
    t->left->height = getHeight(t->left);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
int AVLTree<K, V>::getHeight(Node* node) {
  if (node == NULL) {
    return 0;
  }
  return 1 + std::max(getHeight(node->left), getHeight(node->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* tmp = t->left->right;
    Node* tmp2 = t->left->left;
    t->left->right = t->right;
    t->left->left = tmp;
    t->right = t->left;
    t->left = tmp2;
    swap(t, t->right);
    t->height = getHeight(t);
    t->right->height = getHeight(t->right);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (std::abs(getHeight(subtree->left) - getHeight(subtree->right)) <= 1) {
      subtree->height = getHeight(subtree);
      return;
    }
    if (getHeight(subtree->left) > getHeight(subtree->right)) {
      if (getHeight(subtree->left->left) >= getHeight(subtree->left->right)) {
        rotateRight(subtree);
      } else {
        rotateLeftRight(subtree);
      }
    } else {
      if (getHeight(subtree->right->left) <= getHeight(subtree->right->right)) {
        rotateLeft(subtree);
      } else {
        rotateRightLeft(subtree);
      }
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
      Node* newNode = new Node(key, value);
      subtree = newNode;
      if (root == NULL) {
        root = subtree;
      }
      return;
    }
    if (subtree->key == key) {
      subtree->value = value;
      return;
    }
    if (subtree->key > key) {
      insert(subtree->left, key, value);
      rebalance(subtree);
      return;
    }
    if (subtree->key < key) {
      insert(subtree->right, key, value);
      rebalance(subtree);
      return;
    }
}

template <class K, class V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::findNode(K& key, Node* node) {
  if (node == NULL) {
    return NULL;
  }
  if (node->key == key) {
    return node;
  }
  if (findNode(key, node->left) != NULL) {
    return findNode(key, node->left);
  }
  return findNode(key, node->right);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* curr = subtree->left;
            Node* large = NULL;
            Node* prev = subtree->left;
            int count = 0;
            while (curr != NULL) {
              if (count > 1) {
                prev = prev->right;
              }
              large = curr;
              curr = curr->right;
              count++;
            }
            if (large != NULL) {
              prev->right = large->left;
              swap(large, subtree);
              delete large;
              large = NULL;
            } else {
              Node* tmp = subtree->left;
              subtree->left = tmp->left;
              swap(subtree, tmp);
              delete tmp;
              tmp = NULL;
            }
        } else {
            /* one-child remove */
            // your code here
            if (subtree->left == NULL) {
              Node* tmp = subtree->right;
              subtree->left = subtree->right->left;
              subtree->right = subtree->right->right;
              swap(subtree, tmp);
              delete tmp;
              tmp = NULL;
            } else {
              Node* tmp = subtree->left;
              subtree->right = subtree->left->right;
              subtree->left = subtree->left->left;
              swap(subtree, tmp);
              delete tmp;
              tmp = NULL;
            }
        }
        // your code here
    }
}

template <class K, class V>
typename AVLTree<K,V>::Node* AVLTree<K,V>::getRoot() {
  return root;
}

template <class K, class V>
void AVLTree<K,V>::preot(Node *n) {
    if (n==NULL)
        std::cout << "x";
    else {
        std::cout << "(" << n->key << " ";
        preot(n->left);
        std::cout << " ";
        preot(n->right);
        std::cout << ")";
    }
}
