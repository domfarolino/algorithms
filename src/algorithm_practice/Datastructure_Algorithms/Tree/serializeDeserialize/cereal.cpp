#include <iostream>
#include <string>

// Source: Interview Question
// Source: https://leetcode.com/domfarolino-should-fill-this-out

template <typename T>
struct Node {
  T data;
  Node<T> *left, *right;
  Node(T inData): data(inData), left(nullptr), right(nullptr) {}
};

template <typename T>
void deleteTree(Node<T> *root) {
  if (!root) return;
  deleteTree(root->left);
  deleteTree(root->right);

  delete root;
}

template <typename T>
bool treesEqual(Node<T>* root1, Node<T>* root2) {
  if (!root1 && !root2)
    return true;

  if (!root1 || !root2)
    return false;

  return root1->data == root2->data &&
         treesEqual(root1->left, root2->left) &&
         treesEqual(root1->right, root2->right);
}

/* Serialization algorithms */
template <typename T>
void serializeHelper(Node<T>* root, std::string& returnString) {
  if (!root)
    return;

  returnString += std::to_string(root->data);
  returnString.append(1, ','); // Our number separator.
  serializeHelper(root->left, returnString);
  returnString.append(1, 'R');
  serializeHelper(root->right, returnString);
}

template <typename T>
std::string serialize(Node<T>* root) {
  std::string returnString;

  serializeHelper(root, returnString);
  return returnString;
}

int rootValString(const std::string& serialization, int& i) {
  int originalI = i;
  while (i < serialization.size() && serialization[i] != ',') i++;

  int numberLength = i - originalI;
  if (i < serialization.size()) i++; // skip over ','.
  return std::stoi(serialization.substr(originalI, numberLength), nullptr, 10);
}

/* Deserialization algorithms */
Node<int>* deserializeHelper(const std::string& serialization, int& i) {
  Node<int>* returnRoot = nullptr;
  if (i == serialization.size())
    return returnRoot;

  // Deserialize first value and left subtree if applicable.
  if (serialization[i] != 'R') { // `R` here indicates a null (sub)tree.
    int rootVal = rootValString(serialization, i);
    returnRoot = new Node<int>(rootVal);

    // Deserialize left subtree.
    returnRoot->left = deserializeHelper(serialization, i);
    returnRoot->right = deserializeHelper(serialization, i);
  } else i++;

  return returnRoot;
}

Node<int>* deserialize(const std::string& serialization) {
  // Assert: serialization is a valid tree serialization.

  int i = 0;
  return deserializeHelper(serialization, i);
}

void preorder(Node<int>* root) {
  if (!root)
    return;

  std::cout << root->data << std::endl;
  preorder(root->left);
  preorder(root->right);
}

int main() {
  /*
        1
      /   \
     2     3
          /
         4
        / \
      10   -11
  */

  Node<int>* root = new Node<int>(1);
  root->left = new Node<int>(2);
  root->right = new Node<int>(3);

  root->right->left = new Node<int>(4);
  root->right->left->left = new Node<int>(10);
  root->right->left->right = new Node<int>(-11);

  std::string serializedTree = serialize(root);
  std::cout << "Serialized tree string: " << serializedTree << std::endl;

  Node<int>* deserializedTree = deserialize(serializedTree);
  std::cout << "Serialized and deserialized trees are equal: " << treesEqual(root, deserializedTree) << std::endl;

  deleteTree(root);
  deleteTree(deserializedTree);
  return 0;
}
