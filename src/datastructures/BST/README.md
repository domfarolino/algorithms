# Binary Search Tree

Heaps are critical datastructures, and in this document (and repository) we will be discussing an implementation of a heap called
a min heap (MinHeap). Min heaps are commonly an implementations of a priority queue. Heaps can be thought of as a binary tree in
which every node has a higher priority than both of its children. This is known as our heap invariant, and should always be maintained
for the heap to be valid. In a min heap, a node with the highest priority will have lowest value; thus the root of a min heap will
have the smallest value in the heap.

### Implementation

Heaps are trees often implemented with arrays or vectors. In our case, we'll just be using the
[`Vector`](https://github.com/domfarolino/algorithms/tree/master/src/datastructures/Vector) class that also
appears in this repository. So how do we build a tree with a contiguous array? Consider the array
`[1, 2, 3]`, which would produce the following tree:

```
    1
   / \
  2   3
```

Likewise, the array `[1, 2, 3, 4, 5, 6, 7]` produces:

```
     1
   /   \
  2     3
 / \   / \
4   5 6   7
```

After working out a couple examples, it should be clear that given some index `i` in the array, `i`'s left and right children
will be at indices `i*2 + 1` and `i*2 + 2` respectively. Going from node-to-parent works in a similar manner. Given an index
`i`, `i`'s parent will be at index `(i - 1) / 2`. This can easily be seen by examining the first place this can happen.
Both `1` and `2`'s parent should be `0`, and it so happens that both `(1 - 1) / 2` and `(2 - 1) / 2` are both `0`! These simple
methods of traversing an array-implemented tree will come in handy during insertions and removals.

It is the ability to efficiently insert and remove nodes from heaps that make them so powerful. While inserting and removing nodes
from a heap, we have to be careful to ***always*** maintain our aforementioned heap invariant. In order to see how operations keep
our heap a proper heap, it is easiest to visualize insertions and removals on an already proper heap with several nodes in it.

When inserting a node into a non-edge-case heap (let's say, one with a few nodes), we need to find its proper place in the heap. The
best way to do this is to insert it at the very end of the array which will most likely break the heap property of our structure, and
then fix it by bubbling the newly added element up toward the root until we find its proper place. This operation is called [`bubbleUp()`](#bubbleUp).

When removing a node from a non-edge-case heap, we'll always want to remove the root as it will have the highest priority (lowest value in
a min heap) out of any value. You may think that after removing the root, we'll have to pick one of its children to take its spot, thus
shifting a large portion of the array down. This kind of shifting is expensive with a contiguous structure, like a vector. Removing values
from the end of a contiguous structure is actually really fast though, so we try and do that instead. After "removing" the root, we can just
overwrite its value with the one appearing very last in the vector. We can then [`bubbleDown()`](#bubbleDown) this element, shifting it with
its children (which ultimately chooses the child more fit for its replacement) until it can't go any further.

## Supported operations

 - [`MinHeap()`](#default-constructor)
 - [`size()`](#size)
 - [`empty()`](#empty)
 - [`insert()`](#insert)
 - [`remove()`](#remove)
 - [`peek()`](#peek)
 - [`bubbleUp()`](#bubbleUp)
 - [`bubbleDown()`](#bubbleDown)

----

<a name="default-constructor"></a>
### `MinHeap<T>::MinHeap();`

Our default constructor doesn't really need to do anything.

<a name="size"></a>
### `int MinHeap<T>::size();`

Since we've built, or are using, a good implementation of a vector, this method can just be pass-through to `vector.size()`.

<a name="empty"></a>
### `bool MinHeap<T>::empty();`

Since we've built, or are using, a good implementation of a vector, this method can just be pass-through to `vector.empty()`.

<a name="insert"></a>
### `void MinHeap<T>::insert(T elem);`

As previously mentioned, when inserting an element in a heap we want to push the element to the back of our vector and then
perform [`bubbleUp()`](#bubbleUp) so we can find its right place in the tree. [`bubbleUp()`](#bubbleUp) stops when the element
finally gets to the `0`th index of the array, as it can't bubble up anymore, which is initially the case when we insert an element
into an empty heap so [`bubbleUp()`](#bubbleUp)'s base case will be triggered on first-time insertions.

<a name="remove"></a>
### `void MinHeap<T>::remove();`

As previously mentioned, when removing an element from a heap we want to replace the element at the `0`th position of the vector with
the very last one, and keep bubbling it downward. Before just trying to access `this->vector[this->vector.size() - 1]` we should make
sure the vector (heap) is not empty. This will be our initial conditional. Next we'll just perform the replacement, and
call [`bubbleDown()`](#bubbleDown) with the `0`th index.

<a name="peek"></a>
### `T MinHeap<T>::peek();`

Assuming the heap as at least one element, we'll return the root's value. Since we can't just return a sentinal value if the heap is
empty, we'll throw in this case, instead.

<a name="bubbleUp"></a>
### `void MinHeap<T>::bubbleUp(int index);`

This method will be called with the index of the element we'll be bubbling up. The index will always initially be the last possible position
in the vector, and this method will be called during insertions to maintain our heap invariant. This method will be tail-recursive, or can
equally be written iteratively.

When bubbling up an element, as it goes backwards toward the beginning of the vector we need to ensure that it never goes past the `0`th index.
This will be our base case. First we'll need to determine whether the element at our current index is worth swapping with its parent (a method
for finding a node's parent given the node's index was discussed earlier). To make this determination, we'll need to see if the parent's priority
is strictly less than that of the current node's. If it is, we'll want to swap and then call the function again with the index of the node we
swapped with. Otherwise do nothing.

<a name="bubbleDown"></a>
### `void MinHeap<T>::bubbleDown(int index);`

This method will be called with the index of the element we'll be bubbling down. The index will always initially be `0`, and this
method will be called during removals to maintain our heap invariant. This method will be tail-recursive, or can equally be
written iteratively.

When bubbling down an element, as it goes forward toward the end of the vector we need to ensure that it never goes past the
end (now shortened by one since we just came from a remove operation). This will be our base case. First we'll need to determine
whether the element has children it can swap with. We'll have to calculate children indices and ensure they are within the bounds
of the vector. Next we'll have to see which children, if any, are worth swapping with; that is, which valid children have higher
priorities than the current node. If both children have higher priorities we'll want to always swap with the higher priority
child, else we won't be maintaining our heap invariant (this can be seen with a trivial example).

Since there are a lot of conditions in the previous paragraph, it is easy to get into a huge hairy conditional soup in which a
lot of logic gets duplicated! This can be avoided by not enumerating through each possible outcome with nested conditionals, and
instead running tests linearly and independent of each other while keeping sentinal variables alongside to help you continue. We
can then create a variable whose assignment takes the place of the duplicated logic we'd have in a nested mess, and put our swap
logic after everything.

Note the problem is similar to performing some logic with the max of two variables. Instead of writing:

```cpp
if (a >= b) {
  // tons
  // of
  // logic
  // here
  // with A
} else {
  // tons
  // of
  // logic
  // here
  // with B
}
```

...we opt for:

```cpp
int maxVal = max(a, b);

// tons
// of
// logic written
// once for the max
```

And we get:

```cpp
bool hasLeftChild = false, hasRightChild = false;
int lChildIndex = index * 2 + 1, rChildIndex = index * 2 + 2;

if (lChildIndex < this->vec.size() && this->vec[index] > this->vec[lChildIndex]) hasLeftChild = true;
if (rChildIndex < this->vec.size() && this->vec[index] > this->vec[rChildIndex]) hasRightChild = true;

int indexToSwap;

/**
  * Set indexToSwap equal to the valid index whose
  * value in the vector is the lowest (highest priority)
  */
if (hasLeftChild && hasRightChild) indexToSwap = (this->vec[lChildIndex] <= this->vec[rChildIndex]) ? lChildIndex : rChildIndex;
else if (hasLeftChild) indexToSwap = lChildIndex;
else if (hasRightChild) indexToSwap = rChildIndex;
else return;

T childItem = this->vec[indexToSwap];
this->vec[indexToSwap] = this->vec[index];
this->vec[index] = childItem;
return bubbleDown(indexToSwap);
```
