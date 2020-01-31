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
  TreeNode<T>* find_helper(T, TreeNode<T>*);
  TreeNode<T>* remove_helper(T, TreeNode<T>*);
  void clear_helper(TreeNode<T>*);

  static TreeNode<T>* inorder_successor(TreeNode<T>*, TreeNode<T>*);
  static TreeNode<T>* inorder_predecessor(TreeNode<T>*, TreeNode<T>*);

  static TreeNode<T>* min_helper(TreeNode<T>*);
  static TreeNode<T>* max_helper(TreeNode<T>*);

  void inorder_helper(TreeNode<T>*, std::vector<T>&);
  void preorder_helper(TreeNode<T>*, std::vector<T>&);
  void postorder_helper(TreeNode<T>*, std::vector<T>&);

public:
  binary_search_tree(): root_(nullptr), size_(0) {}

  class iterator {
  public:
    // TODO(domfarolino): Make this a forward-iterator, and eventually a
    // bidirectional iterator.
    using iterator_category = std::input_iterator_tag;
    using value_type = T;
    using difference_type = T;
    using pointer = T*;
    using reference = T&;

    // -------- Iterator functionality --------
    iterator operator++() {
      TreeNode<T>* successor =
        binary_search_tree<T>::inorder_successor(node_, root_);
      *this = iterator(successor, root_);
      return *this;
    }
    iterator operator++(int) {
      TreeNode<T>* successor =
        binary_search_tree<T>::inorder_successor(node_, root_);
      iterator old_iterator = *this;
      *this = iterator(successor, root_);
      return old_iterator;
    }
    bool operator!=(iterator other) const {
      return node_ != other.node_;
    }
    bool operator==(iterator other) const {
      return node_ == other.node_;
    }
    iterator operator--() {
      TreeNode<T>* predecessor =
        binary_search_tree<T>::inorder_predecessor(node_, root_);
      *this = iterator(predecessor, root_);
      return *this;
    }
    iterator operator--(int) {
      TreeNode<T>* predecessor =
        binary_search_tree<T>::inorder_predecessor(node_, root_);
      iterator old_iterator = *this;
      *this = iterator(predecessor, root_);
      return old_iterator;
    }
    value_type operator*() {
      return node_->val;
    }

    iterator(): node_(nullptr), root_(nullptr) {}
  private:
    TreeNode<T> *node_, *root_;
    iterator(TreeNode<T> *in_node, TreeNode<T> *in_root):
      node_(in_node), root_(in_root) {}

    friend binary_search_tree; // It is allowed to invoke the private constructor.
  };

  int size() {
    return size_;
  }

  bool empty() {
    return size_ == 0 && root_ == nullptr;
  }

  iterator begin();
  iterator end();

  void insert(T);
  bool exists(T);
  iterator find(T);
  void remove(T);
  void remove_iterative(T);
  void clear();

  iterator min();
  iterator max();

  std::vector<T> bfs();
  std::vector<T> inorder();
  std::vector<T> preorder();
  std::vector<T> postorder();

  ~binary_search_tree();
};

template <typename T>
typename binary_search_tree<T>::iterator binary_search_tree<T>::begin() {
  return min();
}

template <typename T>
typename binary_search_tree<T>::iterator binary_search_tree<T>::end() {
  return iterator();
}

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
typename binary_search_tree<T>::iterator binary_search_tree<T>::find(T elem) {
  // Run the exists logic to find a node, create an iterator around it, and
  // return it.
  return iterator(find_helper(elem, root_), root_);
}

template <typename T>
TreeNode<T>* binary_search_tree<T>::find_helper(T elem, TreeNode<T>* root) {
  if (!root) return nullptr;
  if (root->val == elem) {
    return root;
  } else if (elem < root->val) {
    return find_helper(elem, root->left);
  } else if (elem > root->val) {
    return find_helper(elem, root->right);
  }

  return nullptr;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
bool binary_search_tree<T>::exists(T elem) {
  return find(elem) != end();
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
// static
TreeNode<T>* binary_search_tree<T>::inorder_successor(TreeNode<T> *elem,
                                                      TreeNode<T> *root) {
  TreeNode<T> *successor = nullptr;
  // If |elem| has a right subtree, this is trivial. Otherwise, we must start at
  // root and do a search.
  if (elem->right) {
    return min_helper(elem->right);
  } else {
    // TODO(domfarolino): Document this better.
    // 1. If |root->val| > |elem->val|, then |root| is a candidate successor for
    // sure, but there could be a better one in |root->left|.
    while (root) {
      if (root->val > elem->val || (root->val == elem->val && root != elem)) {
        successor = root;
        root = root->left;
      } else if (root->val <= elem->val) {
        // 2. Else if |root->val| <= |elem->val|, than the successor must exist in
        // |root->right|. Even if |root->val| == |elem->val|, the success or must
        // be in the right subtree (or does not exist).
        root = root->right;
      } // if.
    } // while.
  }

  return successor;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
// static
TreeNode<T>* binary_search_tree<T>::inorder_predecessor(TreeNode<T> *elem,
                                                        TreeNode<T> *root) {
  TreeNode<T> *predecessor = nullptr;
  if (elem->left) {
    // std::cout << "Quick path, getting max of elem->left" << std::endl;
    predecessor = max_helper(elem->left);
  } else {
    while (root) {
      if (root->val < elem->val) {
        // bool first_condition = (root->val < elem->val);
        // std::cout << "First path " << (first_condition ? "first condition" : "second condition") << std::endl;
        predecessor = root;
        root = root->right;
      } else if (root->val >= elem->val) {
        // std::cout << "Second path" << std::endl;
        root = root->left;
      }
    }
  }

  // int pred_value = predecessor ? predecessor->val : -99;
  // std::cout << "  Return pred: " << pred_value << std::endl;
  return predecessor;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
typename binary_search_tree<T>::iterator binary_search_tree<T>::min() {
  return iterator(min_helper(root_), root_);
}

template <typename T>
// static
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
typename binary_search_tree<T>::iterator binary_search_tree<T>::max() {
  if (!root_) return iterator();
  return iterator(max_helper(root_), root_);
}

// Implemented differently than min_helper() just for fun.
template <typename T>
// static
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
