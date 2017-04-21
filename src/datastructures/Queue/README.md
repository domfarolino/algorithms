# Queue

The queue datastructure functions just like a line at the store, in that the `first` item in is the
`first` item out. Equivalently, the `last` item in is the `last` item out. Consequently, queues are
known as `FIFO` or `LILO` containers. This datastructure is used in graph/tree BFS traversals among
other applications.

Queues are often implemented with a singly linked list as the underlying datastructure, as is this particular
implementation. We maintain an internal linked list which has all of the methods our Queue datastructure will
need to use. Again, the Queue datastructure is merely a SLL wrapper.

## Supported operations

 - [`Queue()`](#default-constructor)
 - [`size()`](#size)
 - [`empty()`](#empty)
 - [`enqueue()`](#enqueue)
 - [`dequeue()`](#dequeue)
 - [`front()`](#front)
 - [`clear()`](#clear)

*Note this class does not explicitly declare a copy constructor or copy-assignment operator because the underlying
datastructures implement these sufficiently. This class is simply a wrapper of the `SLL` class.*

----

<a name="default-constructor"></a>
### `Queue<T>::Queue();`

This does nothing :)

<a name="size"></a>
### `int Queue<T>::size() const;`

Returns the size of the underlying `SLL`.

<a name="empty"></a>
### `bool Queue<T>::empty() const;`

Returns a boolean indicating whether or not the underlying linked list is
[empty](https://github.com/domfarolino/algorithms/tree/master/src/datastructures/SLL#empty).

<a name="enqueue"></a>
### `void Queue<T>::push(T elem);`

This method utilizes [`SLL<T>::addToTail`](https://github.com/domfarolino/algorithms/tree/master/src/datastructures/SLL#addToHead)
to push new elements to the end of the list. When enqueuing elements to a queue, the internal list will evolve as such:

```
1.) NULL
2.) 1 -> NULL
3.) 1 -> 2 -> NULL
4.) 1 -> 2 -> 3 -> NULL
```

<a name="dequeue"></a>
### `void Queue<T>::pop();`

In the opposite nature of [`enqueue()`](#enqueue), this method utilizes
[`SLL<T>::removeFromHead`](https://github.com/domfarolino/algorithms/tree/master/src/datastructures/SLL#removeFromHead)
to remove elements from the head of the underlying linked list. When dequeuing elements from a queue, the internal list
will evolve as such:

```
1.) 1 -> 2 -> 3 -> NULL
2.) 2 -> 3 -> NULL
3.) 3 -> NULL
4.) NULL
```

<a name="front"></a>
### `T Queue<T>::front(T elem) const;`

This method returns the value of the first element (one that has been there the longest) in the internal list
(queue) if there is one, and throws an `std::logic_error` otherwise. We attempt to get the first element in the
list by taking advantage of [`SLL<T>::begin`](https://github.com/domfarolino/algorithms/tree/master/src/datastructures/SLL#begin)
which returns an instance of [`SLLIterator`](https://github.com/domfarolino/algorithms/blob/master/src/datastructures/SLL/SLLIterator.h).

The reason we throw when the list is empty is because we MUST return some real instance of type `T`, therefore `NULL`
would not work since we're not returning a pointer, and we cannot return some sentinal value the user will magically
understand indicates that the list is empty because:

1. These sentinal values (`-1`, `INT_MAX`, `INT_MIN`, etc) may mean different things to different users
1. We don't know what type `T` the user will be using!

<a name="clear"></a>
### `void Queue<T>::clear();`

This method utilizes the underlying `SLL` class to delete the list.
