#pragma once

#include <cstddef>
#include <stack>

// Definition for a binary tree node.
struct TreeNode {
    int val_;
    int balance_;
    TreeNode *left_;
    TreeNode *right_;
    TreeNode(int x) {
      left_ = NULL;
      right_ = NULL;
      val_ = x;
      balance_ = 0;
    }
};

TreeNode* findLastUnbalanced(TreeNode* node);
bool isBalanced(TreeNode* node);
int height(TreeNode* node);
int findLastDeepth(TreeNode* node, int deepth);
void deleteTree(TreeNode* root);
