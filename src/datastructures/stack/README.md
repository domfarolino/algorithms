# Stack

The stack data structure functions just like a stack of plates, in that the `first` item in is the
`last` item out. Equivalently, the `last` item in is the `first` item out. Consequently, stacks are
known as `FILO` or `LIFO` containers. This kind of data structure is often useful to simulate recursive
functions (like DFS), or to reverse the contents of another container.

stacks are often implemented with a singly linked list as the underlying data structure, as is this particular
implementation. We maintain an internal linked list which has all of the methods our stack data structure will
need to use. Again, the stack data structure is merely a linked list wrapper.

## Supported operations

 - [`stack()`](#default-constructor)
 - [`size()`](#size)
 - [`empty()`](#empty)
 - [`push()`](#push)
 - [`pop()`](#pop)
 - [`top()`](#top)
 - [`clear()`](#clear)

*Note this class does not explicitly declare a copy constructor or copy-assignment operator because the underlying
data structures implement these sufficiently. This class is simply a wrapper of the `linked_list` class.*

----

<a name="default-constructor"></a>
### `stack<T>::stack();`

This does nothing :)

<a name="size"></a>
### `int stack<T>::size() const;`

Returns the size of the underlying `linked_list`.

<a name="empty"></a>
### `bool stack<T>::empty() const;`

Returns a boolean indicating whether or not the underlying linked list is
[empty](https://github.com/domfarolino/algorithms/tree/master/src/datastructures/linked_list#empty).

<a name="push"></a>
### `void stack<T>::push(T elem);`

This method utilizes [`linked_list<T>::add_to_head`](https://github.com/domfarolino/algorithms/tree/master/src/datastructures/linked_list#add-to-head)
to push new elements to the front of the list. When pushing elements to a stack, the internal list will evolve as such:

```
1.) NULL
2.) 1 -> NULL
3.) 2 -> 1 -> NULL
4.) 3 -> 2 -> 1 -> NULL
```

<a name="pop"></a>
### `void stack<T>::pop();`

In the opposite nature of [`push()`](#push), this method utilizes
[`linked_list<T>::remove_from_head`](https://github.com/domfarolino/algorithms/tree/master/src/datastructures/linked_list#remove-from-head)
to remove elements from the head of the underlying linked list. When popping elements from a stack, the internal list
will evolve as such:

```
1.) 3 -> 2 -> 1 -> NULL
2.) 2 -> 1 -> NULL
3.) 1 -> NULL
4.) NULL
```

<a name="top"></a>
### `T stack<T>::top(T elem) const;`

This method returns the first element in the internal list if there is one, and throws an `std::logic_error` otherwise.
We attempt to get the first element in the list by taking advantage of
[`linked_list<T>::begin`](https://github.com/domfarolino/algorithms/tree/master/src/datastructures/linked_list#begin), which returns an
instance of `linked_list::iterator`.

The reason we throw when the list is empty is because we MUST return some real instance of type `T`. Therefore, `NULL`
would not work, since we're not returning a pointer, and we cannot return some sentinal value the user will magically
understand indicating the list is empty because:

1. Common sentinal values (`-1`, `INT_MAX`, `INT_MIN`, etc) may mean different things to different users
1. We don't know what type `T` the user will be using!

<a name="clear"></a>
### `void stack<T>::clear();`

This method utilizes the underlying `linked_list` class to delete the list.
