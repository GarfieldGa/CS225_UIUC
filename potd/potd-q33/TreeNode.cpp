#include "TreeNode.h"
#include <algorithm>


void rightRotate(TreeNode* root) {

    // Your code here
    TreeNode* tmp = root->left_;
    if (root->parent_ != NULL) {
      root->parent_->left_ = root->left_;
      tmp->parent_ = root->parent_;
    } else {
      tmp->parent_ = NULL;
    }
    root->left_ = tmp->right_;
    if (tmp->right_ != NULL) {
      tmp->right_->parent_ = root;
    }
    tmp->right_ = root;
    root->parent_ = tmp;
}


void leftRotate(TreeNode* root) {

    // your code here
    TreeNode* tmp = root->right_;
    if (root->parent_ != NULL) {
      root->parent_->right_ = root->right_;
      tmp->parent_ = root->parent_;
    } else {
      tmp->parent_ = NULL;
    }
    root->right_ = tmp->left_;
    if (tmp->left_ != NULL) {
      tmp->left_->parent_ = root;
    }
    tmp->left_ = root;
    root->parent_ = tmp;
}



void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}
