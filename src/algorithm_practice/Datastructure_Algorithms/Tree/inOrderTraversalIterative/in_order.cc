#include <iostream>
#include <vector>
#include <stack>

// Source: https://leetcode.com/problems/binary-tree-inorder-traversal/description/

template <typename T>
struct Node {
  T val;
  Node<T> *left, *right;
  Node(T inData): val(inData), left(nullptr), right(nullptr) {}
};

template <typename T>
void delete_tree(Node<T> *root) {
  if (!root) return;
  delete_tree(root->left);
  delete_tree(root->right);

  delete root;
}

template <typename T>
std::vector<T> in_order_traversal(Node<T>* root) {
  std::vector<T> traversal;
  std::stack<Node<T>*> s;

  Node<T>* current = root;
  while (current || s.size()) {
    while (current) {
      s.push(current);
      current = current->left;
    }

    // |current| == nullptr.
    // Set |current| to the last node we pushed on the stack, simulating the
    // recursion unwinding from the base-case.
    current = s.top();

    // Visit |current|.
    traversal.push_back(current->val);
    s.pop();

    // Start again from |current|'s right subtree. If it exists, we'll continue
    // as normal. If it does not, we'll look at the last value on the stack, if
    // there is one.
    current = current->right;
  }

  return traversal;
}

// This was my original approach to the problem. In some ways it is more
// intuitive to me, though introduces an extra stack unnecessarily.
template <typename T>
std::vector<T> in_order_traversal_original_approach(Node<T>* root) {
  std::vector<T> visited;
  if (!root) return visited;
  std::stack<Node<T>*> untouched, right_child_to_visit;
  untouched.push(root);

  Node<T>* top;
  while (untouched.size() || right_child_to_visit.size()) {
    if (untouched.size()) {
      top = untouched.top();
      untouched.pop();
      if (top->left)
        untouched.push(top->left);
      right_child_to_visit.push(top);
    } else {
      // Assert |right_child_to_visit.size()|.
      top = right_child_to_visit.top();
      visited.push_back(top->val);
      if (top->right)
        untouched.push(top->right);
      right_child_to_visit.pop();
    }
  }

  return visited;
}

int main() {
  Node<int>* root = new Node<int>(5);
    root->left = new Node<int>(2);
      root->left->left = new Node<int>(1);
      root->left->right = new Node<int>(3);
        root->left->right->right = new Node<int>(4);
    root->right = new Node<int>(7);
      root->right->left = new Node<int>(6);
      root->right->right = new Node<int>(8);

  auto traversal = in_order_traversal(root),
       traversal2 = in_order_traversal_original_approach(root);

  for (const int& num : traversal)
    std::cout << num << ", ";
  std::cout << std::endl;

  for (const int& num : traversal2)
    std::cout << num << ", ";
  std::cout << std::endl;


  // Don't forget about our memory.
  delete_tree(root);
  return 0;
}
