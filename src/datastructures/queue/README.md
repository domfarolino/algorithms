# Queue

The queue data structure functions just like a line at the store, in that the `first` item in is the
`first` item out. Equivalently, the `last` item in is the `last` item out. Consequently, queues are
known as `FIFO` or `LILO` containers. This data structure is used in graph/tree BFS traversals, among
other applications.

Queues are often implemented with a singly linked list as the underlying data structure, as is this particular
implementation. We maintain an internal linked list which has all of the methods our queue data structure will
need to use. Again, the queue data structure is merely a `linked_list` wrapper.

## Supported operations

 - [`queue()`](#default-constructor)
 - [`size()`](#size)
 - [`empty()`](#empty)
 - [`enqueue()`](#enqueue)
 - [`dequeue()`](#dequeue)
 - [`front()`](#front)
 - [`clear()`](#clear)

*Note this class does not explicitly declare a copy constructor or copy-assignment operator because the underlying
data structures implement these sufficiently. This class is simply a wrapper of the `linked_list` class.*

----

<a name="default-constructor"></a>
### `queue<T>::queue();`

This does nothing :)

<a name="size"></a>
### `int queue<T>::size() const;`

Returns the size of the underlying `linked_list`.

<a name="empty"></a>
### `bool queue<T>::empty() const;`

Returns a boolean indicating whether or not the underlying linked list is
[empty](https://github.com/domfarolino/algorithms/tree/master/src/datastructures/linked_list#empty).

<a name="enqueue"></a>
### `void queue<T>::enqueue(T elem);`

This method utilizes [`linked_list<T>::add_to_tail`](https://github.com/domfarolino/algorithms/tree/master/src/datastructures/linked_list#add-to-tail)
to push new elements to the end of the list. When enqueuing elements to a queue, the internal list will evolve as such:

```
1.) NULL
2.) 1 -> NULL
3.) 1 -> 2 -> NULL
4.) 1 -> 2 -> 3 -> NULL
```

<a name="dequeue"></a>
### `void queue<T>::dequeue();`

In the opposite nature of [`enqueue()`](#enqueue), this method utilizes
[`linked_list<T>::remove_from_head`](https://github.com/domfarolino/algorithms/tree/master/src/datastructures/linked_list#remove-from-head)
to remove elements from the head of the underlying linked list. When dequeuing elements from a queue, the internal list
will evolve as such:

```
1.) 1 -> 2 -> 3 -> NULL
2.) 2 -> 3 -> NULL
3.) 3 -> NULL
4.) NULL
```

<a name="front"></a>
### `T queue<T>::front(T elem) const;`

This method returns the value of the first element (one that has been there the longest) in the internal list
(queue) if there is one, and throws an `std::logic_error` otherwise. We attempt to get the first element in the
list by taking advantage of [`linked_list<T>::begin`](https://github.com/domfarolino/algorithms/tree/master/src/datastructures/linked_list#begin)
which returns an instance of `linked_list::iterator`.

The reason we throw when the list is empty is because we MUST return some real instance of type `T`. Therefore, `NULL`
would not work, since we're not returning a pointer, and we cannot return some sentinal value the user will magically
understand indicating the list is empty because:

1. Common sentinal values (`-1`, `INT_MAX`, `INT_MIN`, etc) may mean different things to different users
1. We don't know what type `T` the user will be using!

<a name="clear"></a>
### `void queue<T>::clear();`

This method utilizes the underlying `linked_list` class to delete the list.
