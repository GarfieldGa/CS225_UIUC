#include "TreeNode.h"
#include <cmath>
#include <stack>

TreeNode* findLastUnbalanced(TreeNode* node) {
  // your code here
  if (node == NULL) {
    return NULL;
  }
  if (isBalanced(node)) {
    return NULL;
  }
  if (isBalanced(node->left_) && isBalanced(node->right_)) {
    return node;
  }
  if (findLastDeepth(node->left_, 0) > findLastDeepth(node->right_, 0)) {
    return findLastUnbalanced(node->left_);
  } else {
    return findLastUnbalanced(node->right_);
  }
}
int findLastDeepth(TreeNode* node, int deepth) {
  if (node == NULL) {
    return -1;
  }
  int a = findLastDeepth(node->left_, deepth + 1);
  int b = findLastDeepth(node->right_, deepth + 1);
  if (a != -1 && b != -1) {
    return std::max(a, b);
  }
  if (!isBalanced(node)) {
    return deepth;
  }
  return -1;
}

bool isBalanced(TreeNode* node) {
  if (node == NULL) {
    return true;
  }
  if (std::abs(height(node->left_) - height(node->right_)) > 1) {
    return false;
  }
  return isBalanced(node->left_) && isBalanced(node->right_);
}

int height(TreeNode* node) {
  if (node == NULL) {
    return 0;
  }
  return 1 + std::max(height(node->left_), height(node->right_));
}

void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}
