# Singly Linked List

A singly linked list is a datastructure similar to a vector however the elements are not stored contiguously. The nature of this storage
affects the complexities of some of the abstract operations. For example, `addToFront` (equivalent to `push_front`) is `O(1)`, and there is
no indexing. "Indexing" must be done with iteration which is `O(n)`. Singly linked lists work by maintaining an internal list with `head` and
`tail` pointers as well as an internal `_size` variable to keep track of the current list length. In all of our operations it is imporant to
maintain certain invariants, such as

 - Ensuring whenever the `head` is `NULL`, the `tail` is also `NULL` and vice versa so that when iterating from
 head to tail, we iterate only over safe memory.
 - When adding and removing nodes from a list, if at all we bring the list down to a single element, the `head` and
 `tail` pointers *must* be equal.
 - At any given point where the `tail` is not `NULL`, `tail->next` should always equal `NULL`, again for safe iteration.
 - The internal `_size` variable is updated appropriately when nodes are added and removed from the list.

The singly linked list is a very important datastructure and is usually the underlying implementation for both stacks and queues.

## Supported operations

 - [`SLL()`](#default-constructor)
 - [`SLL(const SLL<T>&)`](#copy-constructor)
 - [`operator=(const SLL<T>&)`](#copy-assignment)
 - [`size()`](#size)
 - [`empty()`](#empty)
 - [`addToHead()`](#addToHead)
 - [`addToTail()`](#addToTail)
 - [`removeFromHead()`](#removeFromHead)
 - [`removeFromTail()`](#removeFromTail)
 - [`remove()`](#remove)
 - [`exists()`](#exists)
 - [`clear()`](#clear)

----

<a name="default-constructor"></a>
### `SLL<T>::SLL();`

The default constructor sets both the `head` and `tail` pointers to `NULL`.

<a name="copy-constructor"></a>
### `SLL<T>::SLL(const SLL<T>& right);`

The copy constructor allows support for deep copying when initializing a list with the definition of another.
For example: `SLL<int> list = alreadyExistingList;`. Similarly to a regular constructor, the copy constructor
is generated for you by the compiler unless you explicitly include one. The default copy constructor performs
a shallow copy of internal member variables from one instance to another. Sometimes this is good enough, but
when your internal member variables are pointers pointing to dynamically allocated memory, often you'll want to
take extra steps to ensure that the memory is reallocated (and its contents copied) for each new instance that is
initialized. This is so that multiple instances do now share the same underlying memory. This can lead to logic
errors, double-frees, etc.

<a name="copy-assignment"></a>
### `SLL<T>& SLL<T>::operator=(const SLL<T>& right);`

The logic behind this functionality is nearly identical to [`SLL(const SLL<T>&)`](#copy-constructor).

<a name="size"></a>
### `int SLL<T>::size() const;`

This method returns the internal `_size` variable.

<a name="empty"></a>
### `bool SLL<T>::empty() const;`

This method returns a boolean indicating whether or not the list is empty.

<a name="addToHead"></a>
### `void SLL<T>::addToHead(T elem);`

When adding something to the beginning of the list we'll see one of two cases.

 - The list is empty (`head = tail = NULL`)
 - The list has at least one node (`head != NULL`)

Regarding the former, we just need to set the head equal to a new list node whose value is `elem`. Since the list will only contain
one value at this point it is important to uphold our invariant of updating the tail to equal the head.

In the average case of inserting an element at the head of a list with more than one node we'll just create a new node whose next
value is equal to the current head. Then we'll set the current head equal to this new value, and we're finished.

<a name="addToTail"></a>
### `void SLL<T>::addToTail(T elem);`

Adding an element to the tail of a list functions similarly to adding to the head. If the list is empty the functions behave identically.

In the average case, we just need to make our current tail point to a new node whose value is `elem`. We need to set the `next` field on
this node to `NULL` (prepping it to become a tail), and then set our tail pointer equal to this node.

<a name="removeFromHead"></a>
### `void SLL<T>::removeFromHead();`

When removing an element from the head of a list, besides the case where the list is empty, we'll encounter one of two cases.

 - The list has a single node
 - The list has many nodes

The former is a special case in which we'll need to be sure to maintain our invariant and update the head and tail pointers to `NULL`
after deleting the head.

In general we'll want to reverse what we did in `addToHead` so basically assuming the head exists, we'll want to:

1. Keep a temp pointer equal to `head->next`
1. Delete `head`
1. Set `head` equal to `head->next`

These operations will be the same in both cases, and we can take care of the former case by just checking to see if our new head is `NULL` or
not. If it is, we know we just deleted the tail and we should update our tail pointer. Else, we do nothing.

<a name="removeFromTail"></a>
### `void SLL<T>::removeFromTail();`

When removing *any* element of a list it is convenient to have a pointer to the element that comes before it. Consider the case in which we want
to delete the node `3` in the following list: `2 -> 3 -> 4`. In this case we'll want to seal the gap that deleting `3` creates so we'll need a
pointer to `2`. We run into a similar position when deleting the tail node from a list, since we'll want to update:

 - The new tail's next value to properly point to `NULL`
 - The tail pointer to equal the node that preceded our old tail (inchworm the tail pointer back)

When deleting a node from a non-empty list, this works fine unless the list contains *only* a single element. In this case it is impossible to get
a pointer to the node before it, so we can perform the same logic that we did in `removeFromHead`.

```cpp
  if (!this->tail) return;

  if (this->head == this->tail) {
    return this->removeFromHead();
  }
```

In the average case however, we can iterate through the list with a temporary pointer until this pointer's next is equal to the tail pointer. Our
pointer will be sitting at the node right before our tail and we can proceed to:

1. Delete our tail
1. Set our tail pointer equal to our temporary pointer (inchworm the tail pointer back)
1. Set the temporary pointer's next field equal to `NULL`

```cpp
  Node<T> *curr = this->head;
  while (curr->next != this->tail) {
    curr = curr->next;
  }

  delete this->tail;

  this->tail = curr;
  this->tail->next = NULL; // important!
```

<a name="remove"></a>
### `void SLL<T>::remove(T elem);`

When removing the first element that matches some criteria from *any* position in a linked list, much of the logic covered in the
<a href="#removeFromTail">removeFromTail</a> applies. Of course we first need to check for list existence and only continue if
there is at least one node in the list.

Next we'll want to employ the same logic of iterating a temporary pointer through the list. Since deleting the head is a special case
(as we cannot obtain a pointer to a node before the head) we'll check to see if the head meets our criteria first and then let one of
our previous methods handle the logic for that case. We know that this method will handle all invariants properly so we can make the call
and return with no worries.

In the average case we'll do our regular iteration. In the prior method (<a href="#removeFromTail">removeFromTail</a>) we stopped iterating
through the list when the temporary's next field equaled the tail pointer. In this case we'll stop iterating when `temp->next` equals a node
that matches our criteria (value equivalence, for example).

```cpp
  Node<T> *tmp = this->head;
  while (tmp->next && tmp->next->val != elem) {
    tmp = tmp->next;
  }
```

Of course we have to take in account that there may not be a node in the list that matches our criteria. In this case, before assuming `temp->next` is
the node to delete we should do a quick check.

```cpp
  // Could not find it
  if (!tmp->next) return;
```

Now we can continue deleting `tmp->next`. To do this we want a temporary pointer to `tmp->next->next` (this is safe since at this point we know `tmp->next`
exists). We then delete `tmp->next` and set `tmp->next` equal to the temporary pointer we pulled out earlier. This works well except for the case where the
node we delete happens to also be the tail node, as we're not upholding our invariant of keeping the tail pointer up to date. We can fix this with a simple
conditional before we continue to actually do the deleting.

```cpp
  if (tmp->next == this->tail) {
    this->tail = tmp;
  }

  delete tmp->next;
  tmp->next = next; // seals gap for regular list, or ensures list ends with NULL
```

<a name="exists"></a>
### `void SLL<T>::exists(T elem) const;`

This method is farily trivial. We want to maintain a temporary pointer initialliy equivalent to the head and while it still
exists, iterate through the list checking each node's value against `elem`.

<a name="clear"></a>
### `void SLL<T>::clear();`

The point of this method is to completely delete the list. We do this by iterating through the list deleting the head pointer while keeping
a temporary pointer to the remaining portion of the list (`this->head->next`). Alternatively we could just keep calling
<a href="#removeFromHead">removeFromHead</a> while the head still exists, since we know this method works in all cases and
upholds the necessary invariants.
