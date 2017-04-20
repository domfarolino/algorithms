# Stack

The stack datastructure functions just like a stack of plates, in that the `first` item in is the
`last` item out. Equivalently, the `last` item in is the `first` item out. Consequently, stacks are
known as `FILO` or `LIFO` containers. This kind of datastructure is often useful to simulate recursive
functions (like DFS), or to reverse the contents of another container.

Stacks are often implemented with a singly linked list as the underlying datastructure, as is this particular
implementation. We maintain an internal linked list pointer called `head` as well as a variable to indicate the
size of our list at any time.

## Supported operations

 - [`Stack()`](#default-constructor)
 - [`size()`](#size)
 - [`empty()`](#empty)
 - [`push()`](#push)
 - [`pop()`](#pop)
 - [`top()`](#top)
 - [`clear()`](#clear)

----

<a name="default-constructor"></a>
### `Stack<T>::Stack();`

The default constructor sets `head` to `NULL` and `_size` to `0`.

<a name="size"></a>
### `int Stack<T>::size() const;`

Returns the internal `_size` variable.

<a name="empty"></a>
### `bool Stack<T>::empty() const;`

Returns a boolean indicating whether or not the `_size` variable is `0`.

<a name="push"></a>
### `void Stack<T>::push(T elem);`

This method is an abbreviated version of
[addToHead()][https://github.com/domfarolino/algorithms/tree/master/src/datastructures/SLL#addToHead] found
in the SLL class. No matter what our current linked list `head` is, we'd like to create a new node an insert
it before the current `head`. Of course, we'll then have to update our `head` pointer to reflect the new beginning
of this list. This can be done as such:

```cpp
Node<T> *newHead = new Node<T>(val);
this->head->next = newHead;
this->head = newHead;
```

...or even simpler:

```cpp
this->head = new Node<T>(val, this->head);
```

When pushing elements to a stack, the internal list will evolve as such:

```
1.) NULL
2.) 1 -> NULL
3.) 2 -> 1 -> NULL
4.) 3 -> 2 -> 1 -> NULL
```

<a name="pop"></a>
### `void Stack<T>::pop();`

If there are elements in the list, namely if `_size != 0` or `head != NULL`, this method removes the first element
from the list and advances the `head` pointer by one. We achieve this by keeping a temporary pointer to the node after
the current `head` (`head->next`) which will soon become the new `head`. We delete the current `head` and assign it to
the next node that we saved off to the side.

When popping elements from a stack, the internal list will evolve as such:

```
1.) 3 -> 2 -> 1 -> NULL
2.) 2 -> 1 -> NULL
3.) 1 -> NULL
4.) NULL
```

<a name="top"></a>
### `T Stack<T>::top(T elem) const;`

This method returns the first element in the internal list if there is one, and throws an `std::logic_error` otherwise.

<a name="clear"></a>
### `void Stack<T>::clear();`

This method iteratively deletes the internal list and sets `head = NULL` and `_size = 0`. This is a user-safe method to call, and is
also called from the destructor.
