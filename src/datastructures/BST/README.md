# Binary Search Tree

Binary search trees are very important and popular datastructures, and in this document (and repository) we
will be discussing the operations associated with BSTs and their implementations. A binary search tree is a
binary tree with the condition that given a root node, every node in the root's left subtree is <= the root's
value, and every node in the root's right subtree is > than the root's value, for every node in the tree (that
last recursive bit is the important part!). The exact semantics of this definition (whether or not we allow
duplicate values, or if so, how we handle them) are implementation-specific and not relevant when capturing the
basic mechanics of this fundamental datastructure.

### Implementation

Binary trees have the benefit of being really efficient datastructures for lookup and find
operations under the right conditions. Their common operations can have a time complexity
of `Θ(log(n))` in the best/average case, where `n` is the total number of nodes in the tree.
A common misconception about this datastructure is that these and operations alike are *always*
`O(log(n))`, or `Θ(log(n))` in the worst case. This is not true. Many operations associated with
this datastructure are `O(n)`, because without some extra work there is nothing guaranteeing that
the tree is balanced, and that is when we achieve optimal performance. For example, if I were to
insert 5 increasing values in a row into an empty binary search tree I'll end up with the following
structure:

```
    1
  /   \
 ~     2
      /  \
     ~    3
        /   \
       ~     4
           /   \
          ~     5
```

...which is practically a linked list with some extra wasted space. This gives us no benefit
specific to a BST ADT. We maximize profit of the BST when we keep it balanced. For example, if
I were to insert the values [`5`, `2`, `8`, `1`, `3`, `6`, `9`] into a BST I'd end up with the
following structure:

```
             5
           /   \
          2     8
         / \   / \
        1   3 6   9
```

...which is perfectly balanced, thus allowing us to take advantage of the BST's structure. With the
above structure we can get `O(log(n))` insertions, removals, and lookups since the perfect balance allows
us to cut the number of nodes we have to deal with in half at each recursive call. This is where we get the
reward of `O(log(n))` operations. Often we say in the average case a BST is relatively close to balanced, giving
us efficient `O(log(n))` operations. Of course in the worst case (completely linear), we cannot do better `O(n)`.
There also exist self-balancing BSTs which maintain a near-perfect balance throughout their life, thus always giving
us (amortized) `O(log(n))` operations, but they are out of the scope of the fundamentals :).

I'll also talk about some of the trends found in implementations of tree-style datastructures. A lot
of generic algorithms that reside in datastructures, like `add()` and `remove()`, only need to accept
a single value, the data to insert or delete. With tree-based datastructures, a lot of these algorithms
are recursive; this is a result of the underlying datastructure being defined recursively. These algorithms
start at some node in the tree and figure out how to recurse further down the tree with some logic. The
algorithms are given a node to act as the "`root`" for the current call being made, and recurse down to
either the left or right subtree, or terminate. Initially they must be called with the tree's actual "`root`"
node. This initial call requires access to private data (the tree's "`root`") to set the context for the first
call. To avoid exposing an API that requires private data, often wrapper functions are used to make this
initial call once for the public caller. For example, the public API for `add()` might accept a single value
to add, and would call the recursive `addHelper()` function with this valuem, and the the tree's "`root`"
node (to set the initial context for the future recursive calls). You'll see this pattern being used in the
implementation in this repository.

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

This just returns the value of our internal `_size` variable. We maintain this internal variable
instead of performing an entire tree walk every time we request the size for performance reasons.
This lets gives us `O(1)` size calculations as long as we properly maintain this variable upon
adding and removing nodes from the tree.

<a name="empty"></a>
### `bool BST<T>::empty();`

This just returns whether or not our internal `_size` variable is `0` *and* our internal `root`
variable is `NULL`. Both are important so that we can more easily catch bugs in the case where
we empty the entire tree yet our root is not `NULL` or the `_size` variable is not `0`.

<a name="add"></a>
### `void BST<T>::add(T elem);`

<a name="add-helper"></a>
### `void BST<T>::addHelper(T elem, TreeNode<T> *root);`

To add a node to binary search tree it is best to consider the average case first. So let's take the
following BST:

```
      5
    /   \
   2     7
 /  \   /  \
~    ~ ~    ~
```

Assuming we want to add the value 11 to the tree, we'll start with the root and realize 11 will need
to be placed in 5's right subtree as it is greater than 5. We'll then repeat this logic at the tree
rooted at 5's right subtree, 7. Again 11 is greater than 7 so we'll need to place 11 in 7's right subtree
however 7's subtree is NULL. In this case we don't want to recurse down another level and give a NULL root
to our function as the current root because we'd just end up setting this NULL root equal to a new node and
it would never be attached to anything. When adding a child node to a parent, we need to add the have the parent
in context so that we can add the child directly to it. In other words, we want to stop recursing at the last
non-null node and determine which subtree our value-to-add will go in. Here's a quick visualization of the
recursion:

```
------------stack frame--------------------+
add(root = 5, value = 11)                  |
  if (value > root && root->right) {       |
    add(5->right, 11);                     |
    +---------stack frame------------------+
    |add(root = 7, 11)                     |
    |   if (value > root && root->right) { |
    |     ...                              |
    |   } else (!right) {                  |
    |     7->right = new Node(10);         |
    |   }                                  |
    +--------------------------------------+
                                           |
-------------------------------------------+
  }
```

* Note the above function must take in a root, which will be the tree's private `root` initially. This means that it
must be called from our `add` wrapper function the first time in order to get the private `root`.

With the above statements, it is clear that in general the `addHelper` function will never have to deal with a NULL root
in the average case; this means we won't have to perform any NULL checks in the beginning of our function before accessing
things like `root->left` and `root->right`, since root will always be non-null.

Now it's time to consider the edge case in which the root of the actual tree is NULL. How can our algorithm handle this?
We could of course add a NULL check at the beginning of our function but is a little wasteful since we'd only *need* to
perform the NULL check the very first time, since we just saw that in the average case we'll always have a non-null root.
The smart way to handle this is to cater to the edge case in the wrapper function `add` that calls the recursive `addHelper`
algorithm with the private `root` variable. Here we can check to see if the actual tree's root is NULL or not, and either
create the root for the first time or pass it off to our recursive algorithm. Yeah! We've successfully condensed our edge
case handling logic so that we're not performing extraneous NULL checks when we don't have to.

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
