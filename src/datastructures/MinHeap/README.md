# Heap (Min Heap)

Heaps are critical datastructures, and in this document (and repository) we will be discussing an implementation of a heap called a min heap (MinHeap). Min heaps are commonly an implementations of a priority queue. Heaps can be thought of as a binary tree in which the root has a value (priority) higher than that of both of its children, which are both roots of thier own subtrees. Clearly the definition is recursive.

Heaps are often trees implemented with arrays or vectors. In our case, we'll be using the `Vector` class that appears in this repository. So how do we build a tree as a contiguous array? Consider the array `[1, 2, 3]` which would produce the tree:

```
    1
  /   \
 2     3
```

Likewise, the array `[1, 2, 3, 4, 5]` would produce:

```
     1
   /   \
  2     3
 / \
4   5
```

## Supported operations

 - [`MinHeap()`](#default-constructor)
 - [`size()`](#size)
 - [`empty()`](#empty)
 - [`insert()`](#insert)
 - [`remove()`](#remove)
 - [`peek()`](#peek)

----

<a name="default-constructor"></a>
### `MinHeap<T>::MinHeap();`

The default constructor sets both the `head` and `tail` pointers to `NULL`.

<a name="size"></a>
### `int MinHeap<T>::size();`

<a name="empty"></a>
### `bool MinHeap<T>::empty();`

<a name="insert"></a>
### `void MinHeap<T>::insert(T elem);`

<a name="remove"></a>
### `void MinHeap<T>::remove();`

<a name="peek"></a>
### `T MinHeap<T>::peek();`
