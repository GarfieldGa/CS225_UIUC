#include "TreeNode.h"
#include <cmath>

bool isHeightBalanced(TreeNode* root) {
  // your code here
  if (root == NULL) {
    return true;
  }
  if (std::abs(height(root->left_) - height(root->right_)) > 1) {
    return false;
  }
  return isHeightBalanced(root->left_) && isHeightBalanced(root->right_);
}

int height(TreeNode* node) {
  if (node == NULL) {
    return 0;
  }
  int a = height(node->left_);
  int b = height(node->right_);
  if (a > b) {
    return 1 + a;
  }
  return 1 + b;
}

void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}
