#include <iostream>
#include <vector>
#include <queue>

template <typename T>
struct TreeNode {
  T val;
  TreeNode *left, *right;
  TreeNode(int in_val): val(in_val), left(nullptr), right(nullptr) {}
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

  TreeNode<T>* MinHelper(TreeNode<T>*);
  TreeNode<T>* MaxHelper(TreeNode<T>*);

  void InorderHelper(TreeNode<T>*, std::vector<T>&);
  void PreorderHelper(TreeNode<T>*, std::vector<T>&);
  void PostorderHelper(TreeNode<T>*, std::vector<T>&);

public:
  BinarySearchTree(): root_(nullptr), size_(0) {}

  int Size() {
    return size_;
  }

  bool Empty() {
    return size_ == 0 && root_ == nullptr;
  }

  void Insert(T);
  bool Exists(T);
  void Remove(T);
  void RemoveIterative(T);
  void Clear();

  TreeNode<T>* Min();
  TreeNode<T>* Max();

  std::vector<T> BFS();
  std::vector<T> Inorder();
  std::vector<T> Preorder();
  std::vector<T> Postorder();

  ~BinarySearchTree();
};

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
void BinarySearchTree<T>::Insert(T elem) {
  if (root_ == nullptr) {
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
  if (!root) return nullptr;

  if (elem < root->val) {
    root->left = RemoveHelper(elem, root->left);
  } else if (elem > root->val) {
    root->right = RemoveHelper(elem, root->right);
  } else {
    // Root node is the one to delete

    // Node to delete has either 0 or 1 child
    if (!root->left || !root->right) {
      TreeNode<T> *tmp = nullptr;

      // Pick a living child to succeed this node (if any)
      if (root->left) tmp = root->left;
      if (root->right) tmp = root->right;

      delete root;
      size_--;

      // Return the replacement node (or nullptr if node had no children)
      return tmp;
    }

    // Node has both children
    TreeNode<T> *successor = MinHelper(root->right);
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
   * nullptr if current is the root.
   */
  TreeNode<T> *parent = nullptr, *current = root_;
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
    TreeNode<T>* successor = MinHelper(current->right);

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
        parent->left = nullptr;
      } else {
        parent->right = nullptr;
      }
    } else {
      // Dealing with the root
      root_ = nullptr;
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
TreeNode<T>* BinarySearchTree<T>::Min() {
  return MinHelper(root_);
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::MinHelper(TreeNode<T> *root) {
  if (!root) return root;
  TreeNode<T>* min_node = root;

  while (min_node->left) {
    min_node = min_node->left;
  }

  return min_node;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
TreeNode<T>* BinarySearchTree<T>::Max() {
  if (!root_) return root_;
  return MaxHelper(root_);
}

// Implemented differently than MinHelper() just for fun.
template <typename T>
TreeNode<T>* BinarySearchTree<T>::MaxHelper(TreeNode<T> *root) {
  if (root->right) return MaxHelper(root->right);
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
std::vector<T> BinarySearchTree<T>::Inorder() {
  std::vector<int> return_vec;
  InorderHelper(root_, return_vec);
  return return_vec;
}

template <typename T>
void BinarySearchTree<T>::InorderHelper(TreeNode<T>* root, std::vector<T> &vec) {
  if (!root) return;
  InorderHelper(root->left, vec);
  vec.push_back(root->val);
  InorderHelper(root->right, vec);
}

template <typename T>
std::vector<T> BinarySearchTree<T>::Preorder() {
  std::vector<int> return_vec;
  PreorderHelper(root_, return_vec);
  return return_vec;
}

template <typename T>
void BinarySearchTree<T>::PreorderHelper(TreeNode<T> *root, std::vector<T> &vec) {
  if (!root) return;
  vec.push_back(root->val);
  PreorderHelper(root->left, vec);
  PreorderHelper(root->right, vec);
}

template <typename T>
std::vector<T> BinarySearchTree<T>::Postorder() {
  std::vector<int> return_vec;
  PostorderHelper(root_, return_vec);
  return return_vec;
}

template <typename T>
void BinarySearchTree<T>::PostorderHelper(TreeNode<T>* root, std::vector<T> &vec) {
  if (!root) return;
  PostorderHelper(root->left, vec);
  PostorderHelper(root->right, vec);
  vec.push_back(root->val);
}

/**
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
template <typename T>
std::vector<T> BinarySearchTree<T>::BFS() {
  std::vector<T> return_vec;
  std::queue<TreeNode<T>*> q;

  if (!Empty()) q.push(root_);

  while (!q.empty()) {
    // Push children
    if (q.front()->left) q.push(q.front()->left);
    if (q.front()->right) q.push(q.front()->right);

    // Visit q.front();
    return_vec.push_back(q.front()->val);

    q.pop();
  }

  return return_vec;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
  Clear();
}
