/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <stack>
#include <queue>
#include <vector>
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node* curr) {
  if (curr == NULL) {
    return;
  }
  mirror(curr->left);
  mirror(curr->right);
  Node* tmp = curr->left;
  curr->left = curr->right;
  curr->right = tmp;
}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    if (root == NULL) {
      return true;
    }
    std::stack<Node*> s;
    Node *tmp = NULL;
    Node* r = root;
    while (r != NULL || !s.empty()) {
      while (r != NULL) {
        s.push(r);
        r = r->left;
      }
      r = s.top();
      if (tmp == NULL) {
        tmp = r;
      } else {
        if (r->elem < tmp->elem) {
          return false;
        }
        tmp = r;
      }
      s.pop();
      r = r->right;
    }
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    Node* r = root;
    Node * tmp = NULL;
    bool b = true;
    isOrdered(r, tmp, b);
    return b;
}

template <typename T>
void BinaryTree<T>::isOrdered(Node* &r, Node* & tmp, bool & b) const {
  if (r == NULL) {
    return;
  }
  isOrdered(r->left,tmp, b);
  if (tmp == NULL) {
    tmp = r;
  } else {
    if (r->elem < tmp->elem) {
      b = false;
    }
    tmp = r;
  }
  isOrdered(r->right, tmp, b);
  /*
  if (curr == NULL) {
    return true;
  }
  if (curr->left != NULL && curr->elem < curr->left->elem) {
    return false;
  }
  if (curr->right != NULL && curr->right->elem < curr->elem) {
    return false;
  }
  return isOrdered(curr->left) && isOrdered(curr->right);
  */
}

/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths) const
{
    // your code here
    std::vector<T> path;
    getPath(paths, path, root);
}

template <typename T>
void BinaryTree<T>::getPath(std::vector<std::vector<T>>& paths, std::vector<T> path, Node* node) const {
  if (node == NULL) {
    return;
  }
  if (node->left == NULL && node->right == NULL) {
    path.push_back(node->elem);
    paths.push_back(path);
  }
  path.push_back(node->elem);
  getPath(paths, path, node->left);
  getPath(paths, path, node->right);
}


/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    return sumDistances(root, -1);
}

template <typename T>
int BinaryTree<T>::sumDistances(Node* node, int count) const {
  if (node == NULL) {
    return 0;
  }
  return sumDistances(node->right, count + 1) + sumDistances(node->left, count + 1) + 1 + count;
}
