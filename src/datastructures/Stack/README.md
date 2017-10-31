# Stack

The stack data structure functions just like a stack of plates, in that the `first` item in is the
`last` item out. Equivalently, the `last` item in is the `first` item out. Consequently, stacks are
known as `FILO` or `LIFO` containers. This kind of data structure is often useful to simulate recursive
functions (like DFS), or to reverse the contents of another container.

Stacks are often implemented with a singly linked list as the underlying data structure, as is this particular
implementation. We maintain an internal linked list which has all of the methods our Stack data structure will
need to use. Again, the Stack data structure is merely a SLL wrapper.

## Supported operations

 - [`Stack()`](#default-constructor)
 - [`size()`](#size)
 - [`empty()`](#empty)
 - [`push()`](#push)
 - [`pop()`](#pop)
 - [`top()`](#top)
 - [`clear()`](#clear)

*Note this class does not explicitly declare a copy constructor or copy-assignment operator because the underlying
data structures implement these sufficiently. This class is simply a wrapper of the `SLL` class.*

----

<a name="default-constructor"></a>
### `Stack<T>::Stack();`

This does nothing :)

<a name="size"></a>
### `int Stack<T>::size() const;`

Returns the size of the underlying `SLL`.

<a name="empty"></a>
### `bool Stack<T>::empty() const;`

Returns a boolean indicating whether or not the underlying linked list is
[empty](https://github.com/domfarolino/algorithms/tree/master/src/datastructures/SLL#empty).

<a name="push"></a>
### `void Stack<T>::push(T elem);`

This method utilizes [`SLL<T>::addToHead`](https://github.com/domfarolino/algorithms/tree/master/src/datastructures/SLL#addToHead)
to push new elements to the front of the list. When pushing elements to a stack, the internal list will evolve as such:

```
1.) NULL
2.) 1 -> NULL
3.) 2 -> 1 -> NULL
4.) 3 -> 2 -> 1 -> NULL
```

<a name="pop"></a>
### `void Stack<T>::pop();`

In the opposite nature of [`push()`](#push), this method utilizes
[`SLL<T>::removeFromHead`](https://github.com/domfarolino/algorithms/tree/master/src/datastructures/SLL#removeFromHead)
to remove elements from the head of the underlying linked list. When popping elements from a stack, the internal list
will evolve as such:

```
1.) 3 -> 2 -> 1 -> NULL
2.) 2 -> 1 -> NULL
3.) 1 -> NULL
4.) NULL
```

<a name="top"></a>
### `T Stack<T>::top(T elem) const;`

This method returns the first element in the internal list if there is one, and throws an `std::logic_error` otherwise.
We attempt to get the first element in the list by taking advantage of
[`SLL<T>::begin`](https://github.com/domfarolino/algorithms/tree/master/src/datastructures/SLL#begin), which returns an
instance of [`SLLIterator`](https://github.com/domfarolino/algorithms/blob/master/src/datastructures/SLL/SLLIterator.h).

The reason we throw when the list is empty is because we MUST return some real instance of type `T`. Therefore, `NULL`
would not work, since we're not returning a pointer, and we cannot return some sentinal value the user will magically
understand indicating the list is empty because:

1. These sentinal values (`-1`, `INT_MAX`, `INT_MIN`, etc) may mean different things to different users
1. We don't know what type `T` the user will be using!

<a name="clear"></a>
### `void Stack<T>::clear();`

This method utilizes the underlying `SLL` class to delete the list.
