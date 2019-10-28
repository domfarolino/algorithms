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
class binary_search_tree {
private:
  TreeNode<T>* root_;
  int size_;

  void insert_helper(T, TreeNode<T>*);
  bool exists_helper(T, TreeNode<T>*);
  TreeNode<T>* remove_helper(T, TreeNode<T>*);
  void clear_helper(TreeNode<T>*);

  TreeNode<T>* min_helper(TreeNode<T>*);
  TreeNode<T>* max_helper(TreeNode<T>*);

  void inorder_helper(TreeNode<T>*, std::vector<T>&);
  void preorder_helper(TreeNode<T>*, std::vector<T>&);
  void postorder_helper(TreeNode<T>*, std::vector<T>&);

public:
  binary_search_tree(): root_(nullptr), size_(0) {}

  int size() {
    return size_;
  }

  bool empty() {
    return size_ == 0 && root_ == nullptr;
  }

  void insert(T);
  bool exists(T);
  void remove(T);
  void remove_iterative(T);
  void clear();

  TreeNode<T>* min();
  TreeNode<T>* max();

  std::vector<T> bfs();
  std::vector<T> inorder();
  std::vector<T> preorder();
  std::vector<T> postorder();

  ~binary_search_tree();
};

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
void binary_search_tree<T>::insert(T elem) {
  if (root_ == nullptr) {
    root_ = new TreeNode<T>(elem);
    size_++;
  } else {
    insert_helper(elem, root_);
  }
}

template <typename T>
void binary_search_tree<T>::insert_helper(T elem, TreeNode<T> *root) {
  if (elem <= root->val) {
    if (root->left) {
      insert_helper(elem, root->left);
    } else {
      root->left = new TreeNode<T>(elem);
      size_++;
    }
  } else {
    if (root->right) {
      insert_helper(elem, root->right);
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
bool binary_search_tree<T>::exists(T elem) {
  return exists_helper(elem, root_);
}

template <typename T>
bool binary_search_tree<T>::exists_helper(T elem, TreeNode<T>* root) {
  if (!root) return false;
  if (root->val == elem) {
    return true;
  } else if (elem < root->val) {
    return exists_helper(elem, root->left);
  } else if (elem > root->val) {
    return exists_helper(elem, root->right);
  }

  return false;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
template <typename T>
void binary_search_tree<T>::remove(T elem) {
  root_ = remove_helper(elem, root_);
}

template <typename T>
TreeNode<T>* binary_search_tree<T>::remove_helper(T elem, TreeNode<T> *root) {
  if (!root) return nullptr;

  if (elem < root->val) {
    root->left = remove_helper(elem, root->left);
  } else if (elem > root->val) {
    root->right = remove_helper(elem, root->right);
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
    TreeNode<T> *successor = min_helper(root->right);
    root->val = successor->val;
    root->right = remove_helper(successor->val, root->right);
  }

  return root;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
void binary_search_tree<T>::remove_iterative(T elem) {
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
    TreeNode<T>* successor = min_helper(current->right);

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
TreeNode<T>* binary_search_tree<T>::min() {
  return min_helper(root_);
}

template <typename T>
TreeNode<T>* binary_search_tree<T>::min_helper(TreeNode<T> *root) {
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
TreeNode<T>* binary_search_tree<T>::max() {
  if (!root_) return root_;
  return max_helper(root_);
}

// Implemented differently than min_helper() just for fun.
template <typename T>
TreeNode<T>* binary_search_tree<T>::max_helper(TreeNode<T> *root) {
  if (root->right) return max_helper(root->right);
  else return root;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
template <typename T>
void binary_search_tree<T>::clear() {
  clear_helper(root_);
}

template <typename T>
void binary_search_tree<T>::clear_helper(TreeNode<T>* root) {
  if (!root) return;
  clear_helper(root->left);
  clear_helper(root->right);
  delete root;
  size_--;
}

/**
 * DFS Traversals
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
template <typename T>
std::vector<T> binary_search_tree<T>::inorder() {
  std::vector<int> return_vec;
  inorder_helper(root_, return_vec);
  return return_vec;
}

template <typename T>
void binary_search_tree<T>::inorder_helper(TreeNode<T>* root, std::vector<T> &vec) {
  if (!root) return;
  inorder_helper(root->left, vec);
  vec.push_back(root->val);
  inorder_helper(root->right, vec);
}

template <typename T>
std::vector<T> binary_search_tree<T>::preorder() {
  std::vector<int> return_vec;
  preorder_helper(root_, return_vec);
  return return_vec;
}

template <typename T>
void binary_search_tree<T>::preorder_helper(TreeNode<T> *root, std::vector<T> &vec) {
  if (!root) return;
  vec.push_back(root->val);
  preorder_helper(root->left, vec);
  preorder_helper(root->right, vec);
}

template <typename T>
std::vector<T> binary_search_tree<T>::postorder() {
  std::vector<int> return_vec;
  postorder_helper(root_, return_vec);
  return return_vec;
}

template <typename T>
void binary_search_tree<T>::postorder_helper(TreeNode<T>* root, std::vector<T> &vec) {
  if (!root) return;
  postorder_helper(root->left, vec);
  postorder_helper(root->right, vec);
  vec.push_back(root->val);
}

/**
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
template <typename T>
std::vector<T> binary_search_tree<T>::bfs() {
  std::vector<T> return_vec;
  std::queue<TreeNode<T>*> q;

  if (!empty()) q.push(root_);

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
binary_search_tree<T>::~binary_search_tree() {
  clear();
}
