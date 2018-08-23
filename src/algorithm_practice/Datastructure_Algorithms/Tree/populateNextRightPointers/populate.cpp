#include <iostream>

// Source: https://leetcode.com/problems/populating-next-right-pointers-in-each-node/description/

/**
 * Populating next right pointers in each node
 * This problem is really cool! We are given the wonderful guarantee that the input
 * tree is perfect. Given a NULL tree (NULL root) however, we should return NULL. It
 * makes sense to view this problem as a DFS one, where we perform some operation at each
 * stack frame, and recurse downward. If we were to perform the single operation of populating
 * a node's left child's next pointer with the node's right child at each level, this is incomplete,
 * and would end up with the following style of tree:
 *
 *          1
 *         / \
 *        /   \
 *       /     \
 *      /       \
 *     2-------->3
 *    / \       / \
 *   /   \     /   \
 *  4---->5   6---->7
 *
 * ...and so on downwards, which is a good starting point, however incomplete, due to the fact that
 * a node's grandchildren are not all connected by `next` pointers, even though the immediate children
 * trees are. Just simply performing a child `next` population for each node is not enough, and will lead
 * to split cousins at every branch point. So how can we populate 5's `next` pointer with 6? To do this we'd
 * need access to 5's cousin's tree, which we can observe we have given that 2's `next` pointer has been populated
 * with a reference to it! So, when we handle 5, no only do we want to connect 5's immediate children via `next` pointers,
 * but we also want to connect 5 with its cousin, by setting 5->next = 5->parent->next->left. Note we don't actually have a
 * pointer to the parent when we're observing `5` recursively, so we can actually make this cousin connection at a higher level.
 * In other words, a parent is not only responsible for connecting its children with `next` pointers, but is also responsible for
 * connecting it's right-most child with _it's_ left-most cousin! Again, we can do that fine, because we know all parents (which are
 * just nodes), have a pointer to their sibling. And a parent's sibling's children is the paren't children's cousin. Wordy, I know. So
 * our solution is looking like this:
 *
 * 1.) If given node is NULL, return NULL
 * 2.) root->left->next = root->right
 * 3.) if (root->next)
 *       root->right->next = root->next->left; *we have to perform this check here, since all right-most nodes will never have a populated `next` pointer
 * 4.) Recurse on both left and right children
 *
 * This is good. We connect family trees, which will generalize down to any depth, thus making the entire tree connected by `next` pointers. Check out
 * some examples of this on paper with increasing sizes of the perfect input tree.
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(log(n)), due to stack frames accumulating proportionally to the height of the perfect tree
 *
 * Iterative solution using O(1) space
 *
 * We can make the observation that we might not need to recurse downward in order to perform all of our tasks. Note that normally with tree
 * recursive algorithms, the only way we have access to lateral portions of the tree is from suspended stack frames that we'll get to when the
 * current ones are finished, but here, with these `next` pointers, we actually have complete lateral access to nodes in the tree whenever we're
 * viewing any particular node (because when we view a node, its `next` pointers have been filled out. So what we can do to avoid recursion is:
 * 1.) Store the left-most node of the first level into a variable, `curr`
 * 2.) Make a variable `tmp`, equal to `curr`, and if it is non-NULL and has children, perform the following steps:
 *     a.) tmp->left->next = tmp->right
 *     b.) if (tmp->next)
 *           tmp->right->next = tmp->next->left
 *     c.) tmp = tmp->next
 * 3.) curr = curr->left
 * 4.) Repeat step 2, if `curr` is non-NULL
 *
 * This is really nice, we basically save the left-most node of a given level, and iterate laterally through the tree performing the steps we used
 * to perform recursively. When we get to the end of the tree, we set our left-most node variable equal to the left-most node of the next level, and
 * repeat this until we run out of levels (this left-most node variable is NULL).
 *
 * Complexity analysis:
 * Time complexity: O(n)
 * Space complexity: O(1)
 */

template <typename T>
struct TreeNode {
  T val;
  TreeNode<T> *left, *right, *next;
  TreeNode(T inVal): val(inVal), left(nullptr), right(nullptr), next(nullptr) {}
};

 // This handles all of the edge cases, given the null checks we do in the while
 // loops etc.
template <typename T>
void connect(TreeNode<T>* root) {
  TreeNode<T> *curr = root, *tmp = curr;
  while (curr && curr->left) { // # of levels
    tmp = curr;

    while (tmp) { // # of nodes in given level
      tmp->left->next = tmp->right;
      if (tmp->next)
        tmp->right->next = tmp->next->left;
      tmp = tmp->next;
    }

    curr = curr->left;
  }
}

template <typename T>
bool verifyTree(TreeNode<T> *curr, int n) {
  int count = 0;
  TreeNode<T> *leftTmp = curr;

  while (leftTmp) {
    curr = leftTmp;

    while (curr) {
      std::cout << curr->val << ", ";
      count++;
      curr = curr->next;
    }

    std::cout << "Verifying new level..." << std::endl;
    leftTmp = leftTmp->left;
  }

  std::cout << std::endl;
  return (count == n);
}

int main() {
  TreeNode<int> *root = new TreeNode<int>(1);
  root->left = new TreeNode<int>(2);
  root->right = new TreeNode<int>(3);

  root->left->left = new TreeNode<int>(4);
  root->left->right = new TreeNode<int>(5);

  root->right->left = new TreeNode<int>(6);
  root->right->right = new TreeNode<int>(7);

  bool verifiedTree = verifyTree(root, 7);
  std::cout << "Tree is verified correct: " << verifiedTree << std::endl;

  connect(root);
  verifiedTree = verifyTree(root, 7);
  std::cout << "Tree is verified correct: " << verifiedTree << std::endl;
  return 0;
}
