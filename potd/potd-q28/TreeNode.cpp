#include "TreeNode.h"
#include <queue>
#include <cstddef>
#include <iostream>
using namespace std;

TreeNode::TreeNode() : left_(NULL), right_(NULL) { }

int TreeNode::getHeight() {
  queue<TreeNode*> q;
  int height = -1;
  q.push(this);
  while (!q.empty()) {
    for (unsigned int i = 0; i < q.size(); i++) {
      TreeNode* tmp = q.front();
      q.pop();
      if (tmp->left_ != NULL) {
        q.push(tmp->left_);
      }
      if (tmp->right_ != NULL) {
        q.push(tmp->right_);
      }
    }
    height++;
  }
  return height;
}
