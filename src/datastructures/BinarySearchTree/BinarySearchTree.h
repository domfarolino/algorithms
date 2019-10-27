#include <iostream>
#include <vector>
#include <queue>

template <typename T>
struct TreeNode {
  T val;
  TreeNode *left, *right;
  TreeNode(int in_val): val(in_val), left(NULL), right(NULL) {}
};

template <typename T>
class BinarySearchTree {
private:
  TreeNode<T>* root_;
  int size_;

  void InsertHelper(T, TreeNode<T>*);
  bool ExistsHelper(T, TreeNode<T>*);
  TreeNode<T>* RemoveHelper(T, TreeNode<T>*);
  void ClearHelper(TreeNode<T>*);

  TreeNode<T>* minHelper(TreeNode<T>*);
  TreeNode<T>* maxHelper(TreeNode<T>*);

  void inorderHelper(TreeNode<T>*, std::vector<T>&);
  void preorderHelper(TreeNode<T>*, std::vector<T>&);
  void postorderHelper(TreeNode<T>*, std::vector<T>&);

public:
  BinarySearchTree(): root_(NULL), size_(0) {}

  int size() {
    return size_;
  }

  bool empty() {
    return size_ == 0 && root_ == NULL;
  }

  void Insert(T);
  bool Exists(T);
  void Remove(T);
  void RemoveIterative(T);
  void Clear();

  TreeNode<T>* min();
  TreeNode<T>* max();

  std::vector<T> bfs();
  std::vector<T> inorder();
  std::vector<T> preorder();
  std::vector<T> postorder();

  ~BinarySearchTree();
};

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
void BinarySearchTree<T>::Insert(T elem) {
  if (root_ == NULL) {
    root_ = new TreeNode<T>(elem);
    size_++;
  } else {
    InsertHelper(elem, root_);
  }
}

template <typename T>
void BinarySearchTree<T>::InsertHelper(T elem, TreeNode<T> *root) {
  if (elem <= root->val) {
    if (root->left) {
      InsertHelper(elem, root->left);
    } else {
      root->left = new TreeNode<T>(elem);
      size_++;
    }
  } else {
    if (root->right) {
      InsertHelper(elem, root->right);
    } else {
      root->right = new TreeNode<T>(elem);
      size_++;
    }
  }
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
bool BinarySearchTree<T>::Exists(T elem) {
  return ExistsHelper(elem, root_);
}

template <typename T>
bool BinarySearchTree<T>::ExistsHelper(T elem, TreeNode<T>* root) {
  if (!root) return false;
  if (root->val == elem) {
    return true;
  } else if (elem < root->val) {
    return ExistsHelper(elem, root->left);
  } else if (elem > root->val) {
    return ExistsHelper(elem, root->right);
  }

  return false;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
template <typename T>
void BinarySearchTree<T>::Remove(T elem) {
  root_ = RemoveHelper(elem, root_);
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::RemoveHelper(T elem, TreeNode<T> *root) {
  if (!root) return NULL;

  if (elem < root->val) {
    root->left = RemoveHelper(elem, root->left);
  } else if (elem > root->val) {
    root->right = RemoveHelper(elem, root->right);
  } else {
    // Root node is the one to delete

    // Node to delete has either 0 or 1 child
    if (!root->left || !root->right) {
      TreeNode<T> *tmp = NULL;

      // Pick a living child to succeed this node (if any)
      if (root->left) tmp = root->left;
      if (root->right) tmp = root->right;

      delete root;
      size_--;

      // Return the replacement node (or NULL if node had no children)
      return tmp;
    }

    // Node has both children
    TreeNode<T> *successor = minHelper(root->right);
    root->val = successor->val;
    root->right = RemoveHelper(successor->val, root->right);
  }

  return root;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
void BinarySearchTree<T>::RemoveIterative(T elem) {
  if (!root_) return;

  /**
   * Set current equal to the node-to-remove
   * and parent equal to current's parent, or
   * NULL if current is the root.
   */
  TreeNode<T> *parent = NULL, *current = root_;
  while (current && current->val != elem) {
    parent = current;
    if (elem < current->val) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  if (!current) return;

  /**
   * If current has both children, it's parent
   * doesn't matter and we must find its successor
   * to replace its value, then delete the successor
   */
  if (current->left && current->right) {
    // Find minimum in the right subtree
    TreeNode<T>* successor = minHelper(current->right);

    // Replace node-to-remove's value with its successor's
    current->val = successor->val;

    // Delete node which contained successor
    // value, as this node is now a duplicate
    parent = current;
    current = current->right;
    while (current->left) {
      parent = current;
      current = current->left;
    }

    // Bypass the node we're removing
    if (parent->left == current) {
      parent->left = current->right;
    } else if (parent->right == current) {
      parent->right = current->right;
    }

    delete current;
  } else if (current->left) { // node-to-remove only has left child
    if (parent) {
      /**
       * If the node-to-remove has a parent
       * we can use the parent to bypass the
       * node before we delete it
       */
      if (parent->left == current) {
        parent->left = current->left;
      } else {
        parent->right = current->left;
      }
    } else {
      // Else we're dealing with the root
      root_ = current->left;
    }

    delete current;
  } else if (current->right) {
    if (parent) {
      /**
       * If the node-to-remove has a parent
       * we can use the parent to bypass the
       * node before we delete it
       */
      if (parent->left == current) {
        parent->left = current->right;
      } else {
        parent->right = current->right;
      }
    } else {
      // Else we're dealing with the root
      root_ = current->right;
    }

    delete current;
  } else {
    // Removing a leaf node (maybe root)
    if (parent) {
      // Similar logic to above
      if (parent->left == current) {
        parent->left = NULL;
      } else {
        parent->right = NULL;
      }
    } else {
      // Dealing with the root
      root_ = NULL;
    }
    delete current;
  }

  size_--;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
TreeNode<T>* BinarySearchTree<T>::min() {
  return minHelper(root_);
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::minHelper(TreeNode<T> *root) {
  if (!root) return root;
  TreeNode<T>* minNode = root;

  while (minNode->left) {
    minNode = minNode->left;
  }

  return minNode;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
TreeNode<T>* BinarySearchTree<T>::max() {
  if (!root_) return root_;
  return maxHelper(root_);
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::maxHelper(TreeNode<T> *root) {
  if (root->right) return maxHelper(root->right);
  else return root;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
template <typename T>
void BinarySearchTree<T>::Clear() {
  ClearHelper(root_);
}

template <typename T>
void BinarySearchTree<T>::ClearHelper(TreeNode<T>* root) {
  if (!root) return;
  ClearHelper(root->left);
  ClearHelper(root->right);
  delete root;
  size_--;
}

/**
 * DFS Traversals
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
template <typename T>
std::vector<T> BinarySearchTree<T>::inorder() {
  std::vector<int> returnVec;
  inorderHelper(root_, returnVec);
  return returnVec;
}

template <typename T>
void BinarySearchTree<T>::inorderHelper(TreeNode<T>* root, std::vector<T> &vec) {
  if (!root) return;
  inorderHelper(root->left, vec);
  vec.push_back(root->val);
  inorderHelper(root->right, vec);
}

template <typename T>
std::vector<T> BinarySearchTree<T>::preorder() {
  std::vector<int> returnVec;
  preorderHelper(root_, returnVec);
  return returnVec;
}

template <typename T>
void BinarySearchTree<T>::preorderHelper(TreeNode<T> *root, std::vector<T> &vec) {
  if (!root) return;
  vec.push_back(root->val);
  preorderHelper(root->left, vec);
  preorderHelper(root->right, vec);
}

template <typename T>
std::vector<T> BinarySearchTree<T>::postorder() {
  std::vector<int> returnVec;
  postorderHelper(root_, returnVec);
  return returnVec;
}

template <typename T>
void BinarySearchTree<T>::postorderHelper(TreeNode<T>* root, std::vector<T> &vec) {
  if (!root) return;
  postorderHelper(root->left, vec);
  postorderHelper(root->right, vec);
  vec.push_back(root->val);
}

/**
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
template <typename T>
std::vector<T> BinarySearchTree<T>::bfs() {
  std::vector<T> returnVec;
  std::queue<TreeNode<T>*> q;

  if (!empty()) q.push(root_);

  while (!q.empty()) {
    // Push children
    if (q.front()->left) q.push(q.front()->left);
    if (q.front()->right) q.push(q.front()->right);

    // Visit q.front();
    returnVec.push_back(q.front()->val);

    q.pop();
  }

  return returnVec;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
  Clear();
}
