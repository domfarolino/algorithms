# Binary Search Tree

Binary search trees are very important and popular datastructures, and in this document (and repository) we
will be discussing the operations associated with BSTs and their implementations. A binary search tree is a
binary tree in which given a single node, every node in the tree's left subtree has a value less or equal to
that of the given node, while every node in the tree's right subtree has a value greater than that of the given
node.

### Implementation

Some discussion here about implementation about some misconceptions about performance. For example:
inserts and removals are not `O(log(n))` unless the tree is balanced.

## Supported operations

 - [`BST()`](#default-constructor)
 - [`size()`](#size)
 - [`empty()`](#empty)
 - [`add()`](#add)
 - [`addHelper()`](#add-helper)
 - [`exists()`](#exists)
 - [`existsHelper()`](#exists-helper)
 - [`remove()`](#remove)
 - [`removeHelper()`](#remove-helper)
 - [`clear()`](#clear)
 - [`clearHelper()`](#clear-helper)
 - [`min()`](#min)
 - [`max()`](#max)
 - [`Traversals`](#traversals)

----

<a name="default-constructor"></a>
### `BST<T>::BST();`

Our default constructor doesn't really need to do anything. We just have an initialization
list which sets our internal `root` member pointer to `NULL` and our internal size variable
`_size` to `0`.

<a name="size"></a>
### `int BST<T>::size();`

This just returns the value of our internal `_size` variable.

<a name="empty"></a>
### `bool BST<T>::empty();`

This just returns whether or not our internal `_size` variable is `0` *and* our internal `root`
variable is `NULL`.

<a name="add"></a>
### `void BST<T>::add(T elem);`

Stuff here

<a name="add-helper"></a>
### `void BST<T>::addHelper(T elem, TreeNode<T> *root);`

Stuff here

<a name="exists"></a>
### `void BST<T>::exists(T elem);`

Stuff here

<a name="exists-helper"></a>
### `void BST<T>::existsHelper(T elem, TreeNode<T> *root);`

<a name="remove"></a>
### `void BST<T>::remove(T elem);`

Stuff here

<a name="remove-helper"></a>
### `void BST<T>::removeHelper(T elem, TreeNode<T> *root);`

Stuff here

<a name="clear"></a>
### `void BST<T>::clear(T elem);`

Stuff here

<a name="clear-helper"></a>
### `void BST<T>::clearHelper(T elem, TreeNode<T> *root);`

Stuff here

<a name="min"></a>
### `TreeNode<T> BST<T>::min(T elem, TreeNode<T> *root);`

Stuff here

<a name="max"></a>
### `TreeNode<T> BST<T>::max();`

Stuff here

<a name="traversals"></a>
### Traversals

 - Pre-order ...etc
 - Post-order ...etc
 - In-order ...etc
