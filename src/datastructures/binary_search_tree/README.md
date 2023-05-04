# Binary Search Tree

Binary search trees are very important and popular data structures. In this document (and repository), we
will be discussing the operations associated with BST's and their implementations. A binary search tree is a
binary tree with the condition that, given a root node, every node in the root's left subtree is <= the root's
value and every node in the root's right subtree is > than the root's value. This should hold true for every
node in the tree (this recursive bit is the important part!). The exact semantics of this definition (whether
or not we allow duplicate values, or if so, how we handle them) are implementation-specific. In this
implementation, we'll be allowing duplicates to appear in the left subtree of a given node.

Note that a binary tree is really a specific type of Directed Acyclic Graph (DAG) when relating to graph theory.
While traversals on general graphs apply to all trees, some of the algorithms and traversals in this
implementation are specific to the binary (search) tree data structure.

### Implementation

Binary trees have the benefit of being really efficient data structures for lookup and find
operations, under the right conditions. Their common operations can have a time complexity
of `Θ(log(n))` in the best/average case, where `n` is the total number of nodes in the tree.
A common misconception about this data structure is that these and operations alike are *always*
`O(log(n))`, or `Θ(log(n))` in the worst case. This is not true. Many operations associated with
this data structure are `O(n)` because, without some extra work, there is nothing guaranteeing that
the tree is balanced, which is when we achieve optimal performance. For example, if I were to
insert 5 increasing values in a row into an empty binary search tree, I'll end up with the following
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

...which is practically a glorified linked list with some extra wasted space. This gives us no
benefit specific to the BST ADT. We maximize profit from the BST when we keep it balanced. For
example, if I were to insert the values [`5`, `2`, `8`, `1`, `3`, `6`, `9`] into a BST I'd end
up with the following structure:

```
             5
           /   \
          2     8
         / \   / \
        1   3 6   9
```

...which is perfectly balanced, thus allowing us to take advantage of the BST's structure. With the
above structure, we can get `O(log(n))` insertions, removals, and lookups since the perfect balance allows
us to cut the number of examined nodes in half at each recursive call. This is how we obtain
`O(log(n))` operations. Often, we say in the average case a BST is relatively close to being balanced, thus
giving us efficient `O(log(n))` operations. Of course, in the actual worst case (completely linear), we cannot
do better than `O(n)`. There also exist self-balancing BST's which maintain a near-perfect balance throughout their
life, thus *always* giving us (amortized) `O(log(n))` operations. Maintaining a balanced structure is a little
more difficult and out of the scope of the fundamentals. :)

I'll also talk about some of the trends found in implementations of tree-style data structures. A lot
of generic algorithms that reside in data structures, like `insert()` and `remove()`, only need to accept
a single value, being the data to insert or delete. With tree-based data structures, a lot of these algorithms
are recursive. This is a result of the underlying data structure being defined recursively. These algorithms
start at some node in the tree and figure out how to recurse further down the tree with some logic. The
algorithms are given a node to act as the "`root`" for the current call being made, and recurse down to
either the left or right subtree, or terminate. Initially, they must be called with the tree's actual "`root`"
node. This initial call requires access to private data (the tree's "`root`") to set the context for the first
call. To avoid exposing an API that requires private data, wrapper functions are often used to make this
initial call once for the user. For example, the public API for `insert()` might accept a single value to add,
and then call the recursive `insert_helper()` function with this value along with the tree's "`root`" node
(to set the initial context for the future recursive calls). The `insert_helper` would take it from here, recursing
down the tree as necessary. You'll see this wrapper function pattern being used in the implementation in
this repository.

## Supported operations

### Binary Search Tree class

 - [`binary_search_tree()`](#default-constructor)
 - [`size()`](#size)
 - [`empty()`](#empty)
 - [`insert()`](#insert)
 - [`find()`](#find)
 - [`remove()`](#remove)
 - [`remove_iterative()`](#remove-iterative)
 - [`clear()`](#clear)
 - [`begin()`](#begin)
 - [`end()`](#end)
 - [`min()`](#min)
 - [`max()`](#max)
 - [`inorder_successor()`](#inorder-successor)
 - [`inorder_predecessor()`](#inorder-predecessor)

### Traversals
- [`bfs()`](#bfs)
- [`inorder()`](#inorder)
- [`preorder()`](#preorder)
- [`postorder()`](#postorder)

### Internal iterator class

 - [`iterator()`](#default-constructor-iterator)
 - [`operator++()`](#operator++)
 - [`operator--()`](#operator--)
 - [`operator!=()`](#operator!=)
 - [`operator==()`](#operator==)
 - [`operator*()`](#operator*)

----

## Binary Search Tree class

<a name="default-constructor"></a>
### `binary_search_tree<T>::binary_search_tree();`

Our default constructor doesn't really need to do anything. We just have an initialization
list which sets our internal `root_` member pointer to `nullptr` and our internal `size_` variable
to `0`.

<a name="size"></a>
### `int binary_search_tree<T>::size();`

This just returns the value of our internal `size_` variable. We maintain this internal variable
instead of performing an entire tree walk every time we request the size for performance reasons.
This gives us `O(1)` size calculations as long as we properly maintain this variable when adding
and removing nodes from the tree.

<a name="empty"></a>
### `bool binary_search_tree<T>::empty();`

This just returns whether or not our internal `size_` variable is `0` *and* our internal `root_`
variable is `nullptr`. Both are important so that we can more easily catch bugs in the case where
we empty the entire tree yet our `root_` is not `nullptr` or the `size_` variable is not `0`.

<a name="insert"></a>
### `void binary_search_tree<T>::insert(T elem);`

### `void binary_search_tree<T>::insert_helper(T elem, TreeNode<T> *root);`

To insert a node into a binary search tree, it is best to consider the average case first. So let's
take the following BST:

```
      5
    /   \
   2     7
 /  \   /  \
~    ~ ~    ~
```

Assuming we want to add the value 11 to the tree, we'll start with the root and realize 11 will need
to be placed in 5's right subtree, as it is greater than 5. We'll then repeat this logic at the tree
rooted at 5's right subtree, 7. Again, 11 is greater than 7 so we'll need to place 11 in 7's right subtree,
however, 7's subtree is `nullptr`. In this case, we don't want to recurse down another level and give a `nullptr`
root to our function as the current root. We'd just end up setting this `nullptr` pointer equal to a
new node and it would never actually be attached to anything. When adding a child node to a parent, we
need to have the parent in context so that we can attach the child directly to it. In other words, we
want to stop recursing at the last non-null node and attach a new child to it. Here's a quick visualization
of the recursion:

```
---------------stack frame-----------------+
add(root = 5, value = 11)                  |
  if (value > root && root->right) {       | // if we can recurse further
    add(5->right, 11);                     |
    +---------stack frame------------------+
    |add(root = 7, value = 11)             |
    |   if (value > root && root->right) { | // if we can recurse furhter
    |     //doesn't get reached            |
    |   } else (!root->right) {            | // if we've hit a leaf node, give it a child
    |     7->right = new Node(10);         | // attach the child
    |   }                                  |
    +--------------------------------------+
                                           |
-------------------------------------------+
  }
```

Note the above function must take in a root, which will be the tree's private `root_` initially. This means that it
must be called from our `add` wrapper function the first time in order to get the private `root_`.

With the above statements, it is clear that, in general, the `addHelper` function will never have to deal with a `nullptr`
root in the average case. This means we won't have to perform any `nullptr` checks in the beginning of our function before
accessing things like `root->left` and `root->right`, since root will always be non-null.

Now it's time to consider the edge case in which the root of the actual tree is `nullptr` (tree is empty). How can our algorithm
handle this? We could of course add a `nullptr` check at the beginning of our function, though this is a little wasteful since we'd
only *need* to perform this `nullptr` check the very first time, since we just saw that in the average case we'll always be given
a non-null root. The smart way to handle this is to cater to the edge case in the wrapper function `add` that calls the
recursive `addHelper` algorithm. Here, we're going to be dealing with the private `root_` variable so we can check to see if
the actual tree's `root_ = nullptr` before passing it along. If so, we can create the root, thus adding the very first
node in the tree. If not, we can pass it along like we normally would. Yeah! We've successfully condensed our edge case
handling logic so we're not performing extraneous nullptr checks when unnecessary.

<a name="find"></a>
### `iterator binary_search_tree<T>::find(T elem);`

This method delegates to the find\_helper() method below, calling it with the tree's private root to
kick things off. It returns an iterator wrapping its return value.

### `TreeNode<T>* binary_search_tree<T>::find_helper(T elem, TreeNode<T> *root);`

The `find` and `find_helper` methods have similar mechanics to the `insert` method above, so a lot
of the boilerplate will be skipped. The idea behind this algorithm is fairly intuitive in that we
just want to recurse down the tree until we either:

 1. Find the node we're looking for
 1. Or get to a `nullptr` node (the one we're looking for didn't exist)

In the average case of a full tree with our node somewhere in the tree, we'll eventually recurse
downward comparing the value we're given against the value of the current frame's root node. We'll
start the whole thing off with the actual root of the tree, suggesting we'll need a wrapper function
to kick this off. When recursing downward, there is no need to check if the subtree we're about to
recurse to is `nullptr` before we recurse like we did with `add`; instead we can just recurse to it
and check in the next frame if that root is `nullptr`. Doing both would yield in extraneous `nullptr`
checks.

With this information, we know the wrapper function `find` doesn't have to provide any logic at all.
It simply kicks off the first call of the `find_helper` with the private root of the tree.

<a name="remove"></a>
### `void binary_search_tree<T>::remove(T elem);`

### `void binary_search_tree<T>::remove_helper(T elem, TreeNode<T> *root);`

Removing a node from a BST is more difficult than adding or finding and, since most sources tend to show the solution with little
or poor explanation, I intend to start with the basics to explain how this algorithm works. There are only three cases to consider
when removing a node from a binary search tree:

  1. The node-to-remove has no children (is a leaf node)
  1. The node-to-remove has one child
  1. The node-to-remove has two children

Of course, there is the trivial case in which the node-to-remove does not exist in the tree. However that's not what we're focusing
on, as we pretty much get that for free.

#### Removing a node with no children

Consider the following tree:

```
  5
   \
    6
```

Removing `6` from the above tree is as easy as navigating to the node (we've already seen how to do this) and simply deleting
it, as its removal doesn't affect any other part of the tree. This is very similar to deleting the tail of a linked list.

#### Removing a node with one child

Consider the following tree:

```
  5
   \
    6
     \
      8
     / \
    7   9
```

Removing `6` from the above tree is as easy as making the `5->right` pointer point to the node-to-remove's only subtree
(thus bypassing our target node) and then deleting `6`. We'd end up with the following tree:

```
  5
   \
    8    // 6 got bypassed and then deleted
   / \
  7   9
```

This is very similar to deleting any middle-node in a linked list.

### Removing a node with two children (most complex case)

Consider the following tree:

```
      5
    /   \
   2     7
    \   / \
     4 6   8
```

Removing `5` from the above tree is a bit less obvious, mainly because its successor is not completely straightforward. It is
tempting to think that we must pick either the `2` or `7` to replace the `5`, but that requires us to rearrange a lot of the
tree afterwards. Instead, we can pick a successor that requires practically no extra work, the closest
value to the node we're removing. The two closest values to `5` in the tree will be the maximum node in its left subtree (`4`),
and the minimum node in its right subtree (`6`). Note that no matter which we choose as a successor, no rearranging will be
required. This is because the smallest node in `5`'s right subtree (`6`) is still larger than all nodes in `5`'s left subtree,
meaning `5`'s left subtree can also be the left subtree of `6`. Since `6` is the smallest node in `5`'s right subtree, all
nodes in this subtree can equally comprise the right subtree of `6` upon succession. So the question at this point is which do
we choose, the `4` or the `6` as the successor? You might think it doesn't matter but it actually does! Consider the following
tree:

```
      5
   /     \
  2       7
   \     /
    3   6
   /   /
  3   6
```

The two trees we can get as a result of choosing either `3` or `6` as `5`'s successor are as follows:

```
 Choose 3         Choose 6
     3       |      6
  /     \    |    /   \
 2       7   |   2     7
  \     /    |    \   /
   3   6     |     3 6
      /      |    /
     6       |   3
```

Note only one of the above trees is valid! Remember the invariant that we introduced in the first paragraph that talks about how
we handle duplicates? You may recall that given any node `n`, the nodes in `n`'s left subtree will have values <= `n`'s
value, meaning duplicates of a particular node will only appear in the node's left subtree. The tree on the right in the above
example breaks this invariant because `6` has a duplicate in its right subtree when we promote it to the new root. In short, if
we allow duplicates in the left subtree of a particular node, we must always *choose our successor from the node-to-remove's left
subtree* to maintain this invariant upon succession. This is a minor but possibly important detail that, as stated in the first
paragraph of this document, depends on exactly how an implementation chooses to handle duplicates.

Finally, to actually achieve the structure above, we want to replace the value of `5` with the value of `3`. This will leave us with
an extra `3` in the left subtree since we just copied its value. At this point, we can call the `removeHelper` algorithm on `3`,
starting at the left subtree of the node whose value just got replaced. Removing the extra `3` is guaranteed to be a trivial
operation since it is the maximum value in the left subtree, therefore it can have at most one child. Thus, we've successfully
boiled down the case of deleting a node with two children into performing a simple copy, and deleting a node with at most one child!

#### Implementation

The implementation of this algorithm is a little tricky, but you'll notice that in the above sections we made many comparisons to
removing nodes from a linked list. A BST is basically a more complex linked list, and the traversal required to find a node in a BST
is similar to that of a linked list. Once found, deleting a node from a BST is basically the same as deleting one in a linked list in
`2/3` possible cases. In the third more complicated case, we simply perform a value copy and boil the problem down into a trivial
case. Let's first consider how we'd iteratively and recursively delete a node from a linked list.

We can write a function to iteratively delete a node from a linked list rather simply. Assuming the node-to-remove is not the
list's `head` (an edge case), we'd create a temp node pointer `tmp`, initially set to the `head` of the list, and iterate forward
until `tmp->next` points to the node-to-remove. We stop when `tmp->next` is our target node because we must have a
reference to the node before the one we wish to delete in order to seal the gap once we delete it. We can implement basically
the same logic with a BST (see the `removeIterative` method), however many tree algorithms are naturally recursive,
which can actually cut down on the complexity of our logic. The space complexity of the iterative solution will also be much
cheaper.

When recursively deleting a node from a linked list, we'll start at the `head` node and recurse forward on each `head->next` until
we find the node-to-remove. Since recursion is just an accumulation of stack frames, let's consider an arbitrary frame when thinking
about how this algorithm works. Let's assume we're looking at the `head` of a list in some stack frame. If `head` contains the value
we wish to remove, we'll simply delete it and return `head->next`. If it doesn't, we assume the node-to-remove exists somewhere later
in the list and recurse onto `head->next`. Notice though, `head->next` may be a different node once the recursion is complete due to
the nature of the algorithm. If `head->next` is removed, the node after `head->next` will be returned in its place. This means we
should set `head->next = deleteNode(head->next, targetValue)` when we recurse forward in case the next node did get deleted. This
assignment is idempotent otherwise. Notice how in the iterative version we needed a reference to the node before the one we wished
to delete, whereas with recursion this reference is kept implicitly for us in the form of stack frames. This simplifies our logic
because we can focus on deleting the current `head` of any arbitrary stack frame and navigate accordingly.

The recursive `remove_helper` member function behaves very similarly to the aforementioned algorithm though, there is additional
logic to navigate the `left` and `right` children properly, as opposed to `next`, and some value copying logic for when
we wish to delete a node which has two children. Once we perform the copy, we can just call the recursive algorithm on the
left subtree to remove the duplicate successor's value (the trivial case).

<a name="remove-iterative"></a>
### `void binary_search_tree<T>::remove_iterative(T elem);`

This method is undocumented at the moment, though part of its logic is expressed in
<a href="#remove">remove/remove_helper</a>. See the source.

<a name="clear"></a>
### `void binary_search_tree<T>::clear(T elem);`

### `void binary_search_tree<T>::clear_helper(T elem, TreeNode<T> *root);`

This is a basic DFS algorithm to completely delete a tree. The idea is we can only delete a node
once both its left and right subtrees are completely deleted. Since the tree structure is defined
recursively, our algorithm can recurse downwards, re-visiting a node once both of its subtrees are
cleared and it's time to delete the local root. The internal `size_` variable should decrement every
time a node is deleted.

<a name="begin"></a>
### `iterator binary_search_tree<T>::begin();`

Simply delegates to <a href="#min">min</a>.

<a name="end"></a>
### `iterator binary_search_tree<T>::end();`

This is an unfortunately naive method. Ideally, we'd return an iterator pointing past
<a href="#max">max()</a>, and whose <a href="#operator--">operator--</a> returns the max()
iterator. The simple implementation we have now simply returns an iterator that wraps a null node
and is useless. It is only good for equality comparisons for out-of-bound iterators. This is
immediately useful to support the example below, but is ultimately deficient:

```
std::accumulate(tree.begin(), tree.end() /* trivial, but allows us to terminate */, 0);
```

See https://github.com/domfarolino/algorithms/issues/146.

<a name="min"></a>
### `iterator binary_search_tree<T>::min();`

This method is fairly trivial. Given some `root`, we want to traverse as far down its left subtree
as we can go, as this is where smaller and smaller values will exist. The node we end up with should
have no left child. Finally we'll return an iterator that wraps this node.

<a name="max"></a>
### `iterator binary_search_tree<T>::max();`

Same as <a href="#min">min</a> but for the maximum value instead of the minimum.

<a name="inorder-successor"></a>
#### `binary_search_tree<T>::inorder_successor(TreeNode<T> *elem, TreeNode<T> *root);`

This method takes the root of a tree and some existing node in the tree, and returns the node's
inorder successor, or `nullptr` if one does not exist.

This algorithm is trivial if `elem` has a right subtree, since the inorder successor is simply the
minimum of such subtree. Otherwise, we have to start at `root` and work our way down, looking for
candidate inorder successor nodes along the way.

As we work our way down from the root, each node `curr` we encounter will fall into one of two
simple cases (not considering duplicates in our tree):

  1. `curr->val > elem->val`
     - In which case we consider `curr` a candidate inorder successor, but want to traverse its left
       subtree, looking for a more minimal inorder successor
  1. `curr->val <= elem->val`
     - Simple enough: `curr` doesn't give us what we're looking for, so we have no new inorder
       successor, and must follow `curr->right`. This is safe even when `curr->val == elem->val`,
       because we know `curr` does not have a right subtree if we get to these steps, so our traversal
       will stop

That's the basic logic, but how do we handle duplicates? Let's consider a simple tree with 3,
5-valued nodes. In the below-tree, I've labeled each node with an extra identifier indicating the
order in which each would appear in an inorder traversal.

```
    5(3)
   /
  5(2)
 /
5(1)
```

Suppose we start with the `min()` node of the tree whose value is 5(1), and we want to produce its
inorder successor, which is 5(2). What modifications to the above algorithm will need to be made?
Since 5(1) does not have a right subtree, we don't fall into the trivial case, and we have to invoke
the above steps. Clearly we'll start by evalulating the root 5(3) as `curr`, and obviously we want
to go down its left subtree, meaning we'll want to satisfy condition (1) above. That way we can mark
5(3) as our candidate inorder successor, and keep exploring its left subtree. This implies that
we'll want to modify condition (1) to be something more lenient, like:

> 1. `curr->val >= elem->val`

So let's see if that will work. After one iteration we end up with the following

```
    5(3) <-- candidate inorder successor
   /
  5(2) <-- new `curr` node
 /
5(1)
```

And after another iteration we end up with:

```
    5(3)
   /
  5(2) <-- candidate inorder successor
 /
5(1) <-- new `curr` node
```

You can see that another iteration would break our algorithm, since we'd mark 5(1) as our candidate
inorder successor, and ultimately return the same node we started with. Instead, we need to make a
slightly more nuanced modification to condition (1):

> 1. `curr->val > elem->val || (curr->val == elem->val && curr != elem)`

In other words, we want to go left if `curr` is a greater inorder successor, or we also want to find
the left-most value of a given duplicate just above `elem`. Now try and convince yourself that this
works assuming `elem` is 5(2) as well, and so on.

Condition (2) can remain untouched, as for every other kind of node, we'll simply want to explore
the right subtree to find a candidate inorder successor, or nullptr otherwise.

<a name="inorder-predecessor"></a>
#### `binary_search_tree<T>::inorder_predecessor(TreeNode<T> *elem, TreeNode<T> *root);`

This method complements <a href="#inorder-successor">inorder_sucesssor()</a>. Similarly, when given
a node and tasked to find its inorder predecessor, there is a trivial case. When `elem` has a left
subtree, the inorder predecessor is simply the maximum node the left subtree. You can see that this
even works when the predecessor has several duplicates (using similar notation as we did in
<a href="#inorder-sucessor">inorder_successor()</a>):

```
    5
   /
  3(2)
 /
3(1)
```

An inorder traversal of this tree yields the list `[3(1), 3(2), 5]`, indicating the inorder
predecessor of the 5 node is 3(2). This is exactly the node that finding the max node in 5's left
subtree will return. Furthermore we can demonstrate that this works when `elem` is one of several
duplicate values as well:

```
     5(3) <-- elem
    /
   5(2)
  /
 3
  \
   5(1)
```

An inorder traversal of this tree is `[3, 5(1), 5(2), 5(3)]`, and starting with 5(3), our algorithm
above will correctly produce 5(2). From there we'll start with 5(2), and you can see we'll produce
5(1) by finding the maximum value in the subtree rooted at 3. From here, 5(1) does not have a left
subtree, so we no longer fall into the trivial case. Let's see how we can make the rest of our
algorithm work.

When the given node does not have a left subtree, we'll have to start from the root and work our way
down. Each node we come across will fall into one of two simple cases:

  1. `curr->val < elem->val`
     - Here, `curr` is a valid inorder predecessor, so we'll keep track of it, but we should explore
       the right subtree, to attempt to find a more maximal predecessor
  1. `curr->val >= elem->val`
     - When `curr`'s value is greater than our node's value, we don't have what we need, so all we
       can do is traverse the left subtree in hopes of finding something closer to what we want.
     - Even if `curr`'s value is the same as our node's value, all we've come across is a duplicate
       successor (unless `curr == elem`), so we still want to continue down the left subtree. In
       fact, even if `curr` and `elem` are the same node, going down the left subtree is still safe;
       we know the left subtree doesn't exist, and going down it will stop our traversal

The algorithm described by the above conditions can feel a bit nuanced, so let's see how it plays
out with a few good examples that exercise the above conditions (and deal with duplicates):

```
  4
   \
   10
  /
 5 <-- elem
  \
   8
```

First we'll start with the root node 4. We satisfy condition (1) above, so we'll mark it as a
potential inorder predecessor and explore its right subtree, looking for a better one. Next we'll
explore 10, which satisfies condition (2) above. We don't get what we're looking for here, so we
simply move to its left subtree. Now our `curr` node is the same as `elem`; of course the values are
equivalent, which satisfies condition (2). We move to the left subtree, and finish our traversal.

Since our last potential inorder predecessor was the 4 node, we'll return it. That's all folks!

Now for a more complicated one involving duplicates:

```
      4(3)
      / \
   4(2)  5(3)
    /   /
 4(1)  5(2) <-- elem
      /
     5(1)
```

The above tree has the same notation that we've been using to indicate the relative ordering between
nodes with the duplicate values. We're given `elem` which is the 5(2) node, and the correct inorder
predecessor to return would be 5(1). Starting our algorithm out, we realize that `elem` has a left
subtree, which brings us to our trivial case. We return the maximum node in 5(2)'s left subtree,
which is consequently 5(1)...correct!

```
      4(3)
      / \
   4(2)  5(3)
    /   /
 4(1)  5(2)
      /
     5(1) <-- elem
```

Running our algorithm again, we know we should be returning 4(3) as the inorder predecessor. We
start with the root again, 4(3). This satisfies condition (1), so we consider it a candidate inorder
predecessor, and search its right subtree for a potentially better one. We come across 5(3), which
matches condition (2). Our steps critically dont consider it as anything (since duplicates of `elem`
appearing before `elem` can only be sucessors), and we move to the left subtree. This continues
until we hit `nullptr` and stop traversing. We then return our last candidate inorder predecessor,
which is 4(3)!

With those examples, the reader is encouraged to run through the following cases with the below tree
to gain even more insight into why our algorithm works correctly, even with duplicates in our tree.

  - Start at 5(2), and find the predecessor node
  - Start at 5(1), and find the successor node

```
    5(2)
   /
  3
   \
    5(1)
```

---
### Traversals

<a name="bfs"></a>
### `std::vector<T> binary_search_tree<T>::bfs();`
This method returns a vector with the elements from the BST in breadth-first search order. Breadth-first search begins at the root node and then vists all nodes level by level. 

In order to place each value into a vector in BFS order, we need use a queue. First the root is placed into the front of a queue. Then we can use a while loop to push the children into the queue. With each loop, if there is a left subtree or a right subtree that child is pushed into the queue. Then we add the first element of the queue into the vector and dequeue it from the queue. The while loop will run until the queue is empty, which means each node from the tree was inserted into the vector.

<a name="inorder"></a>
### `std::vector<T> binary_search_tree<T>::inorder();`
This method delegates to the `inorder_helper()` method below. This method returns a vector with the elements from the BST in order.

### `void binary_search_tree<T>::inorder_helper(TreeNode<T>* root, std::vector<T> &vec);`
In order to be able to insert the elements of a BST into a vector, in order, we first need to traverse down the root's left subtree.

 The `inorder_helper(root->left, vec)` method is used to traverse as far down the left subtree as we can go. Once we end up with a node with no left child, we add the value to the vector with `vec.push_back(root->val)`.

 After that we simply use `inorder_helper(root->right)` to traverse down the right subtree, searching for another left subtree (and then once exhausted, another right subtree).

<a name="preorder"></a>
### `std::vector<T> binary_search_tree<T>::preorder();`
This method delegates to the `preorder_helper()` method below. This method returns a vector with the elements from the BST in preorder.

### `void binary_search_tree<T>::preorder_helper(TreeNode<T>* root, std::vector<T> &vec);`
The order this method works is as follows:
- Add the root's value to the vector.
- Recursively traverse the left subtree.
- Recursively traverse the right subtree.

First we add the root's value to the vector with `vec.push_back(root->val)` then we traverse down the left subtree. To do this, `preorder_helper(root->left, vec)` is called. Once we reach a node with no left child, `preorder_helper(root->right, vec)` is called to traverse the node's right subtree.

<a name="postorder"></a>
### `std::vector<T> binary_search_tree<T>::postorder();`
This method delegeates to the `postorder_helper()` method below. This method returns a vector with the elements from the BST in post order.

### `void binary_search_tree<T>::postorder_helper(TreeNode<T>* root, std::vector<T> &vec);`
In order to traverse the tree in post order, we need to first traverse down the left subtree. We recursively call `postorder_helper(root->left, vec)` on the node's left subtree to do this. Then we traverse down the right subtree by recursively calling `postorder_helper(root->right, vec)` on the node's right subtree. After that, the value of the current node is inserted into the vector with `vec.push_back(root->val)`.

----

## Internal iterator class

<a name="default-constructor-iterator"></a>
### `iterator::iterator(TreeNode<T> *in_node, TreeNode<T> *root);`

The internal `binary_search_tree<T>::iterator` class provides iterator functionality
for our binary search tree implementation. It is a relatively simple class that acts
as a thin layer of abstraction over a single node, and the root of the tree that the
node belongs in. The class's constructor (private) consumes these two members.

The iterator class implements `std::forward_iterator_tag` support, but see
https://github.com/domfarolino/algorithms/issues/146 to track support of
`std::bidirectional_iterator_tag`.

The implementation is simple, but deficient in some ways. For example, if you have an
iterator representing some node, and the root of that node's tree is deleted, the iterator
is invalidated since it holds a pointer to the deleted root. This is not good, and could be
avoided if the tree supported parent pointers, because the iterator class would no longer need
to hold a root reference.

<a name="operator++"></a>
### `iterator iterator::operator++();`

### `iterator iterator::operator++(int);`

The pre- and post-increment iterator operators delegate to the tree class's
<a href="#inorder-successor">inorder_successor()</a> method to compute the inorder successor of its
internal node, given the internal node and root. Then the correct new iterator is returned
(depending on whether we're pre- or post-incrementing).

<a name="operator--"></a>
### `iterator iterator::operator--();`

### `iterator iterator::operator--(int);`

The pre- and post-decrement iterator operators delegate to the tree class's
<a href="#inorder-predecessor">inorder_predecessor()</a> method to compute the inorder predecessor
of its internal node, given the internal node and root. Then the correct new iterator is returned
(depending on whether we're pre- or post-decrementing).

<a name="operator!="></a>
### `bool iterator::operator!=(iterator other) const`

Returns whether the internal node is not the same as `other`'s internal node.

<a name="operator=="></a>
### `bool iterator::operator==(iterator other) const;`

Returns whether the internal node is the same as `other`'s internal node.

<a name="operator*"></a>
### `T iterator::operator*() const;`

Attempts to dereference the internal node, and returns its `val` member, of type `T`.
