/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (curDim >= Dim) {
      return false;
    }
    if (first[curDim] == second[curDim]) {
      return first < second;
    }
    if (first[curDim] < second[curDim]) {
      return true;
    }
    return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double sum1 = 0;
     double sum2 = 0;
     for (int i = 0;  i < Dim; i++) {
       sum1 += pow(currentBest[i] - target[i], 2);
       sum2 += pow(potential[i] - target[i], 2);
     }
     if (sum1 == sum2) {
       return potential < currentBest;
     }
     if (sum1 > sum2) {
       return true;
     }
     return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     if (newPoints.empty()) {
       root = NULL;
       size = 0;
     } else {
       vector<Point<Dim>> points = newPoints;
       size = 0;
       quickConstruct(points, 0, points.size() - 1, 0, root);
     }
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   this->root = copyNode(other.root);
   size = other.size;
}

template<int Dim>
void KDTree<Dim>::quickConstruct(vector<Point<Dim>>& newPoints, int a, int b, int dim, KDTreeNode*& curr) {
  if (a > b) {
    return;
  }
  Point<Dim> mid = quickSelect(newPoints, a, b, (a+b)/2, dim);
  size++;
  curr = new KDTreeNode(mid);
  if (curr == NULL) {
    return;
  }
  quickConstruct(newPoints, a, (a+b)/2 - 1, (dim+1)%Dim, curr->left);
  quickConstruct(newPoints, (a+b)/2 + 1, b, (dim+1)%Dim, curr->right);
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& newPoints, int a, int b, int pivot, int dim) {
  Point<Dim> pivotValue = newPoints[pivot];
  swap(newPoints[pivot], newPoints[b]);
  int storeIndex = a;
  for (int i = a; i < b; i++) {
    if (smallerDimVal(newPoints[i], pivotValue, dim)) {
      swap(newPoints[storeIndex], newPoints[i]);
      storeIndex++;
    }
  }
  swap(newPoints[b], newPoints[storeIndex]);
  return storeIndex;
}

template <int Dim>
Point<Dim> KDTree<Dim>::quickSelect(vector<Point<Dim>>& newPoints, int a, int b, int k, int dim) {
  if (a == b) {
    newPoints[a];
  }
  int pivot = (a+b) / 2;
  pivot = partition(newPoints, a, b, pivot, dim);
  if (k == pivot) {
    return newPoints[k];
  }
  if (k < pivot) {
    return quickSelect(newPoints, a, pivot-1, k, dim);
  } else {
    return quickSelect(newPoints, pivot+1, b, k, dim);
  }
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  deleteTree(root);
  root = copyNode(rhs.root);
  size = rhs.size;
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   deleteTree(root);
   size = 0;
}

template<int Dim>
void KDTree<Dim>::deleteTree(KDTreeNode* node) {
  if (node == NULL) {
    return;
  }
  deleteTree(node->left);
  deleteTree(node->right);
  delete node;
  node = NULL;
}

template<int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copyNode(KDTreeNode* other) {
  if (other == NULL) {
    return;
  }
  KDTreeNode* node = new KDTreeNode();
  node->point = other->point;
  node->left = copyNode(other->left);
  node->rigth = copyNode(other->right);
  return node;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return findBest(query, root, 0);
}

template<int Dim>
Point<Dim> KDTree<Dim>::findBest(const Point<Dim>& query, KDTreeNode* curr, int dim) const {
  Point<Dim> curr_best = curr->point;
  if (curr->left == NULL && curr->right == NULL) {
    return curr->point;
  }
  if (smallerDimVal(query, curr->point, dim)) {
    if (curr->left != NULL) {
      curr_best = findBest(query, curr->left, (dim+1)%Dim);
    }
  } else {
    if (curr->right != NULL) {
      curr_best = findBest(query, curr->right, (dim+1)%Dim);
    }
  }
  if (shouldReplace(query, curr_best, curr->point)) {
    curr_best = curr->point;
  }

  double curr_R = 0.0;
  double curr_D = pow(curr->point[dim] - query[dim], 2);
  for (int i = 0; i < Dim; i++) {
    curr_R += pow(curr_best[i] - query[i], 2);
  }
  Point<Dim> next_best;
  if (curr_D <= curr_R) {
    if (smallerDimVal(query, curr->point, dim)) {
      if (curr->right != NULL) {
        next_best = findBest(query, curr->right, (dim+1)%Dim);
      }
    } else {
      if (curr->left != NULL) {
        next_best = findBest(query, curr->left, (dim+1)%Dim);
      }
    }
    if (shouldReplace(query, curr_best, next_best)) {
      curr_best = next_best;
    }
  }
  return curr_best;
}
