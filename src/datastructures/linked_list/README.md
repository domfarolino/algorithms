# Singly Linked List

A singly linked list is a data structure similar to a vector, however, the elements are not stored contiguously. The nature of this storage
affects the complexities of some of the abstract operations. For example, `add_to_head` (equivalent to `push_front`) is `O(1)` and there is
no indexing. "Indexing" must be done with iteration over the list, which is `O(n)`. Singly linked lists work by maintaining an internal list
with `head` and `tail` pointers, as well as an internal `size` variable to keep track of the current list length. In all of our operations,
it is important to maintain certain invariants, such as:

 - Ensuring whenever the `head` is `nullptr`, the `tail` is also `nullptr` and vice versa so that when iterating from
 head to tail, we iterate only over safe memory.
 - When adding and removing nodes from a list, if we ever bring the list down to a single element, the `head` and
 `tail` pointers *must* be equal.
 - At any given point where the `tail` is not `nullptr`, `tail->next` should always equal `nullptr`, again for safe iteration.
 - The internal `size` variable is updated appropriately when nodes are added and removed from the list.

The singly linked list is called "singly" because head list node has a _single_ pointer to the next node. This contrasts with
doubly linked lists, where each list node pointers to the next and previous nodes. Linked lists are very important data structure
and are often the underlying implementation for both stacks and queues.

## Supported operations

 - [`linked_list()`](#default-constructor)
 - [`linked_list(const linked_list<T>&)`](#copy-constructor)
 - [`operator=(linked_list<T>)`](#copy-assignment)
 - [`size()`](#size)
 - [`empty()`](#empty)
 - [`add_to_head()`](#add-to-head)
 - [`add_to_tail()`](#add-to-tail)
 - [`remove_from_head()`](#remove-from-head)
 - [`remove_from_tail()`](#remove-from-tail)
 - [`remove()`](#remove)
 - [`exists()`](#exists)
 - [`clear()`](#clear)
 - [`begin()`](#begin)
 - [`end()`](#end)

----

<a name="default-constructor"></a>
### `linked_list<T>::linked_list();`

The default constructor sets both the `head` and `tail` pointers to `nullptr`.

<a name="copy-constructor"></a>
### `linked_list<T>::linked_list(const linked_list<T>& other);`

The copy constructor allows support for deep copying when initializing a list with the definition of another.
For example: `linked_list<int> list = alreadyExistingList;`. Similar to a regular constructor, the copy constructor
is generated for you by the compiler unless you explicitly include one. The default copy constructor performs
a shallow copy of internal member variables from one instance to another. Sometimes this is good enough, but
when your internal member variables are pointers pointing to dynamically allocated memory, often you'll want to
take extra steps to ensure that the memory is reallocated (and its contents copied) for each new instance that is
initialized. This is so that multiple instances do not share the same underlying memory. This can lead to logic
errors, double-frees, etc.

<a name="copy-assignment"></a>
### `linked_list<T>& linked_list<T>::operator=(linked_list<T> other);`

A lot of the logic that is necessary for the copy assignment operator to work can be found in the
[`linked_list(const linked_list<T>&)`](#copy-constructor). To avoid duplicating the code in two places, we can instead
use the copy-swap idiom to define our copy-assignment operator in terms of our copy constructor.

Good sources to understand this idiom:

 - http://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
 - http://stackoverflow.com/questions/5695548/public-friend-swap-member-function

<a name="size"></a>
### `int linked_list<T>::size() const;`

This method returns the internal `size` variable.

<a name="empty"></a>
### `bool linked_list<T>::empty() const;`

This method returns a boolean indicating whether or not the list is empty.

<a name="add-to-head"></a>
### `void linked_list<T>::add_to_head(T elem);`

When adding something to the beginning of the list we'll see one of two cases.

 - The list is empty (`head = tail = nullptr`)
 - The list has at least one node (`head != nullptr`)

Regarding the former, we just need to set the head equal to a new list node whose value is `elem`. Since the list will only contain
one value at this point, it is important to uphold our invariant of updating the tail to equal the head.

In the average case of inserting an element at the head of a list with more than one node, we'll just create a new node whose next
value is equal to the current head. Then, we'll set the current head equal to this new value and we're finished.

<a name="add-to-tail"></a>
### `void linked_list<T>::add_to_tail(T elem);`

Adding an element to the tail of a list functions similarly to adding to the head. If the list is empty, the functions behave identically.

In the average case, we just need to make our current tail point to a new node whose value is `elem`. We need to set the `next` field on
this node to `nullptr` (prepping it to become a tail), and then set our tail pointer equal to this node.

<a name="remove-from-head"></a>
### `void linked_list<T>::remove_from_head();`

When removing an element from the head of a list, besides the case where the list is empty, we'll encounter one of two cases.

 - The list has a single node
 - The list has many nodes

The former is a special case in which we'll need to be sure to maintain our invariant and update the head and tail pointers to `nullptr`
after deleting the head.

In general, we'll want to reverse what we did in `add_to_head`. So basically assuming the head exists, we'll want to:

1. Keep a temp pointer equal to `head->next`
1. Delete `head`
1. Set `head` equal to `head->next`

These operations will be the same in both cases. We can take care of the former case by just checking to see if our new head is `nullptr` or
not. If it is, we know we just deleted the tail and should update our tail pointer. Else, we do nothing.

<a name="remove-from-tail"></a>
### `void linked_list<T>::remove_from_tail();`

When removing *any* element of a list, it is convenient to have a pointer to the element that comes before it. Consider the case in which we want
to delete the node `3` in the following list: `2 -> 3 -> 4`. In this case, we'll want to seal the gap that deleting `3` creates, so we'll need a
pointer to `2`. We run into a similar position when deleting the tail node from a list, since we'll want to update:

 - The new tail's next value to properly point to `nullptr`
 - The tail pointer to equal the node that preceded our old tail (inchworm the tail pointer back)

When deleting a node from a non-empty list, this works fine unless the list contains *only* a single element. In this case it is impossible to get
a pointer to the node before it, so we can perform the same logic that we did in `remove_from_head`.

```cpp
  if (!tail) return;

  if (head == tail) {
    return remove_from_head();
  }
```

In the average case, however, we can iterate through the list with a temporary pointer until this pointer's next is equal to the tail pointer. Our
pointer will be sitting at the node right before our tail and we can proceed to:

1. Delete our tail
1. Set our tail pointer equal to our temporary pointer (inchworm the tail pointer back)
1. Set the temporary pointer's next field equal to `nullptr`

```cpp
  Node<T> *curr = head;
  while (curr->next != tail) {
    curr = curr->next;
  }

  delete tail;

  tail = curr;
  tail->next = nullptr; // important!
```

<a name="remove"></a>
### `void linked_list<T>::remove(T elem);`

When removing the first element that matches some criteria from *any* position in a linked list, much of the logic covered in the
<a href="#remove-from-tail">remove_from_tail</a> applies. Of course, we first need to check for list existence and only continue if
there is at least one node in the list.

Next, we'll want to employ the same logic of iterating a temporary pointer through the list. Since deleting the head is a special case
(as we cannot obtain a pointer to a node before the head), we'll check to see if the head meets our criteria first. If it does, we'll
let one of our previous methods handle the logic for that case. We know that this method will handle all invariants properly so we can
make the call and return with no worries.

In the average case, we'll do our regular iteration. In the prior method (<a href="#remove-from-tail">remove_from_tail</a>), we stopped iterating
through the list when the temporary's next field equaled the tail pointer. In this case, we'll stop iterating when `temp->next` equals a node
that matches our criteria (value equivalence, for example).

```cpp
  Node<T> *tmp = head;
  while (tmp->next && tmp->next->val != elem) {
    tmp = tmp->next;
  }
```

Of course, we have to take into account that there may not be a node in the list that matches our criteria. In this case, before assuming
`temp->next` is the node to delete, we should do a quick check.

```cpp
  // Could not find it
  if (!tmp->next) return;
```

Now we can continue deleting `tmp->next`. To do this, we want a temporary pointer to `tmp->next->next` (this is safe since at this point we know `tmp->next`
exists). We then delete `tmp->next` and set `tmp->next` equal to the temporary pointer we pulled out earlier. This works well except for the case where the
node we delete happens to also be the tail node, as we're not upholding our invariant of keeping the tail pointer up to date. We can fix this with a simple
conditional before we continue to actually do the deleting.

```cpp
  if (tmp->next == tail) {
    tail = tmp;
  }

  delete tmp->next;
  tmp->next = next; // seals gap for regular list, or ensures list ends with nullptr
```

<a name="exists"></a>
### `void linked_list<T>::exists(T elem) const;`

This method is fairly trivial. We want to maintain a temporary pointer initially equivalent to the head and, while it still
exists, iterate through the list checking each node's value against `elem`.

<a name="clear"></a>
### `void linked_list<T>::clear();`

The point of this method is to completely delete the list. We do this by iterating through the list deleting the head pointer while keeping
a temporary pointer to the remaining portion of the list (`head->next`). Alternatively, we could just keep calling
<a href="#remove-from-head">remove_from_head</a> while the head still exists, since we know this method works in all cases and
upholds the necessary invariants.

<a name="begin"></a>
### `linked_list<T>::iterator linked_list<T>::begin();`

This method returns a `linked_list::iterator` object (light abstraction over a `Node<T>` pointer) pointing at the head of the linked list
it was called on. This is useful to iterate through the list and see values in sequence. For more information on the capabilities
of this basic `linked_list::iterator` object, see its definition in the `linked_list` class.

<a name="end"></a>
### `linked_list<T>::iterator linked_list<T>::end();`

This method returns a `linked_list::iterator` object (light abstraction over a `Node<T>` pointer) referencing the nullptr, or more specifically the
value of `tail->next` if tail is not `nullptr`, or `tail` otherwise. This is convenient for iterating so that we can move an
iterator through the list `while (someIterator != list.end())`, and we'll be able to hit all of our elements. See, if `list.end()`
returned a `linked_list::iterator` pointing at the tail, then we'd be able to iterate over all elements BUT the tail!
