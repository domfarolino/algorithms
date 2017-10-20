#include <iostream>
#include <vector>
#include <queue>

template <typename T>
struct TreeNode {
  T val;
  TreeNode *left, *right;
  TreeNode(int inVal): val(inVal), left(NULL), right(NULL) {}
};

template <typename T>
class BST {
private:
  TreeNode<T> *root;
  int _size;

  void addHelper(T, TreeNode<T>*);
  bool existsHelper(T, TreeNode<T>*);
  TreeNode<T>* removeHelper(T, TreeNode<T>*);
  void clearHelper(TreeNode<T>*);

  TreeNode<T>* minHelper(TreeNode<T>*);
  TreeNode<T>* maxHelper(TreeNode<T>*);

  void inorderHelper(TreeNode<T>*, std::vector<T>&);
  void preorderHelper(TreeNode<T>*, std::vector<T>&);
  void postorderHelper(TreeNode<T>*, std::vector<T>&);


public:
  BST(): root(NULL), _size(0) {}

  int size() {
    return this->_size;
  }

  bool empty() {
    return this->_size == 0 && this->root == NULL;
  }

  void add(T);
  bool exists(T);
  void remove(T);
  void removeIterative(T);
  void clear();

  TreeNode<T>* min();
  TreeNode<T>* max();

  std::vector<T> bfs();
  std::vector<T> inorder();
  std::vector<T> preorder();
  std::vector<T> postorder();

  ~BST();
};

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
void BST<T>::add(T elem) {
  if (this->root == NULL) {
    this->root = new TreeNode<T>(elem);
    this->_size++;
  } else {
    this->addHelper(elem, this->root);
  }
}

template <typename T>
void BST<T>::addHelper(T elem, TreeNode<T> *root) {
  if (elem <= root->val) {
    if (root->left) {
      addHelper(elem, root->left);
    } else {
      root->left = new TreeNode<T>(elem);
      this->_size++;
    }
  } else {
    if (root->right) {
      addHelper(elem, root->right);
    } else {
      root->right = new TreeNode<T>(elem);
      this->_size++;
    }
  }
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
bool BST<T>::exists(T elem) {
  return existsHelper(elem, this->root);
}

template <typename T>
bool BST<T>::existsHelper(T elem, TreeNode<T>* root) {
  if (!root) return false;
  if (root->val == elem) {
    return true;
  } else if (elem < root->val) {
    return existsHelper(elem, root->left);
  } else if (elem > root->val) {
    return existsHelper(elem, root->right);
  }

  return false;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
template <typename T>
void BST<T>::remove(T elem) {
  this->root = removeHelper(elem, this->root);
}

template <typename T>
TreeNode<T>* BST<T>::removeHelper(T elem, TreeNode<T> *root) {
  if (!root) return NULL;

  if (elem < root->val) {
    root->left = removeHelper(elem, root->left);
  } else if (elem > root->val) {
    root->right = removeHelper(elem, root->right);
  } else {
    // Root node is the one to delete

    // Node to delete has either 0 or 1 child
    if (!root->left || !root->right) {
      TreeNode<T> *tmp = NULL;

      // Pick a living child to succeed this node (if any)
      if (root->left) tmp = root->left;
      if (root->right) tmp = root->right;

      delete root;
      this->_size--;

      // Return the replacement node (or NULL if node had no children)
      return tmp;
    }

    // Node has both children
    TreeNode<T> *successor = minHelper(root->right);
    root->val = successor->val;
    root->right = removeHelper(successor->val, root->right);
  }

  return root;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
void BST<T>::removeIterative(T elem) {
  if (!root) return;

  /**
   * Set current equal to the node-to-remove
   * and parent equal to current's parent, or
   * NULL if current is the root.
   */
  TreeNode<T> *parent = NULL, *current = root;
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
      root = current->left;
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
      root = current->right;
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
      root = NULL;
    }
    delete current;
  }

  this->_size--;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
template <typename T>
TreeNode<T>* BST<T>::min() {
  return minHelper(this->root);
}

template <typename T>
TreeNode<T>* BST<T>::minHelper(TreeNode<T> *root) {
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
TreeNode<T>* BST<T>::max() {
  if (!this->root) return this->root;
  return maxHelper(this->root);
}

template <typename T>
TreeNode<T>* BST<T>::maxHelper(TreeNode<T> *root) {
  if (root->right) return maxHelper(root->right);
  else return root;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
template <typename T>
void BST<T>::clear() {
  clearHelper(this->root);
}

template <typename T>
void BST<T>::clearHelper(TreeNode<T>* root) {
  if (!root) return;
  clearHelper(root->left);
  clearHelper(root->right);
  delete root;
  this->_size--;
}

/**
 * DFS Traversals
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
template <typename T>
std::vector<T> BST<T>::inorder() {
  std::vector<int> returnVec;
  inorderHelper(this->root, returnVec);
  return returnVec;
}

template <typename T>
void BST<T>::inorderHelper(TreeNode<T>* root, std::vector<T> &vec) {
  if (!root) return;
  inorderHelper(root->left, vec);
  vec.push_back(root->val);
  inorderHelper(root->right, vec);
}

template <typename T>
std::vector<T> BST<T>::preorder() {
  std::vector<int> returnVec;
  preorderHelper(this->root, returnVec);
  return returnVec;
}

template <typename T>
void BST<T>::preorderHelper(TreeNode<T> *root, std::vector<T> &vec) {
  if (!root) return;
  vec.push_back(root->val);
  preorderHelper(root->left, vec);
  preorderHelper(root->right, vec);
}

template <typename T>
std::vector<T> BST<T>::postorder() {
  std::vector<int> returnVec;
  postorderHelper(this->root, returnVec);
  return returnVec;
}

template <typename T>
void BST<T>::postorderHelper(TreeNode<T>* root, std::vector<T> &vec) {
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
std::vector<T> BST<T>::bfs() {
  std::vector<T> returnVec;
  std::queue<TreeNode<T>*> q;

  if (!empty()) q.push(this->root);

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
BST<T>::~BST() {
  clear();
}
