# Vector

A vector is a datastructure that acts as a dynamic array with abstract operations. All elements in a vector are stored contiguously
which yields `O(1)` indexing. The Vector class works by maintaining an internal array along with variables to keep track of size and
capacity. Once the size of the internal array matches its capacity (when enough elements are added) the internal array doubles in capacity.
Doubling capacity has proven to be a good way to achieve amortized `O(1)` `push_back`s.

## Supported operations

 - [`Vector()`](#default-constructor)
 - [`Vector(int)`](#overloaded-constructor)
 - [`Vector(const Vector<T>&)`](#copy-constructor)
 - [`operator=(const Vector<T>&)`](#copy-assignment)
 - [`size()`](#size)
 - [`capacity()`](#capacity)
 - [`empty()`](#empty)
 - [`push_back()`](#push_back)
 - [`push_front()`](#push_front)
 - [`pop_back()`](#pop_back)
 - [`pop_front()`](#pop_front)
 - [`reverse()`](#reverse)
 - [`operator[](int)`](#brackets)
 - [`clear()`](#clear)

----

<a name="default-constructor"></a>
### `Vector<T>::Vector();`

The default constructor sets the internal size to 0 since no elements have been added, and the internal capacity to 1 so we can
double the size of the internal array when an element is added. If the capacity were initially set to 0 then we'd have to do some
funny logic when doubling the size of our internal array when trying to add the first element because doubling 0 yields 0.

<a name="overloaded-constructor"></a>
### `Vector<T>::Vector(int inCapacity);`

This overloaded constructor sets the internal size to 0 since no elements have been added, and the internal capacity to
`max(1, int inCapacity)` so we can guarantee that we'll be able to double the size of our internal array when capacity is
met. The `max` check ensures that the capacity will never be 0 or negative.

<a name="copy-constructor"></a>
### `Vector<T>::Vector(const Vector<T>& right);`

The copy constructor allows support for deep copying when code like `Vector<int> vec = alreadyExistingVector;`. Similarly to
a regular constructor, the copy constructor is generated for you by the compiler unless you explicitly include one. The one
generated for you performs shallow copying of internal member variables from one instance to another. Sometimes this is good
enough, but when your internal member variables are pointers pointing to dynamically allocated memory, often you'll want to take
extra steps to ensure that the memory is re-allocated (and its contents copied) for each new instance that is initialized.

<a name="copy-assignment"></a>
### `Vector<T>& Vector<T>::operator=(const Vector<T>& right);`

The logic behind this functionality is nearly identical to [`Vector(const Vector<T>&)`](#copy-constructor).

<a name="size"></a>
### `int Vector<T>::size() const;`

Returns the number of elements in the internal array.

<a name="capacity"></a>
### `int Vector<T>::capacity() const;`

Returns the number of elements the internal array can hold before a resize is necessary.

<a name="empty"></a>
### `bool Vector<T>::empty() const;`

Returns a boolean indicating whether or not the size is 0.

<a name="push_back"></a>
### `void Vector<T>::push_back(T elem);`

When trying to add an element into the vector we will face one of two cases. Either:

 - The size of the internal array has met its capacity, and we'll need to do a resize before pushing back
 - We can simply push back with no problem
overloaded
We first check to see if we must perform a resize. If so, we create another array of length `this->_capacity * 2` and copy
all of the elements from our internal array into the longer one and then double our internal capacity variable. With our data
copied over, we can delete our internal array and set our internal array equal to the newly created one.

Finally we deal with the average case where we have remaining space in our array, and continue to push an element to the back.
This is done by adding the element to the internal array and incrementing the size variable (this is part of the invariant that
keeps this variable always accurate).

\*Note the reason I *DO NOT* double the internal capacity variable before allocating the new array when performing a resize is
because in the event where `new` allocation fails/throws, we've then incorrectly modified our internal capacity variable and
abruptly left the function. This can lead to runtime errors in the future as our internal capacity variable is not guaranteed to
be safe.

<a name="push_front"></a>
### `void Vector<T>::push_front(T elem);`

A capacity check and possible resize will need to be performed up front just as we did in <a href="#push_back">push_back</a>, though
with slightly different mechanics. If we're trying to add a value to an already full internal array we'll need to create a new one of
double capacity like before, and copy our elements to this new array offset by one (leaving room at the beginning). Copying elements
from one array to another with some offset is trivial.

Let's consider the case in which we add an element to a less-than-full array. We'll need to do this copying/shifting in place. Given an
array like `[1, 2, 3, x]` we'll want to shift everything such that the array becomes `[x, 1, 2, 3]` where `x` denotes an empty spot. This
is most easily performed by interating from the back to the front simply shifting values over by one. Think about it. The intermediate steps
of this algorithm would produce:

```
[1, 2, 3, x]
[1, 2, 3, 3]
[1, 2, 2, 3]
[1, 1, 2, 3]
[x, 1, 2, 3]
```

as it pulls all the values over by one. This procedure can also be done starting at the beginning while maintaining
two `tmp` variables, and is slightly more complex.

Finally we proceed to add an element to the front of the array by setting `this->_data[0] = elem` and incrementing our
internal size variable (invariant for state accuracy).

<a name="pop_back"></a>
### `void Vector<T>::pop_back();`

If the internal array is not already empty, decrement internal size variable to make the element at the last position inaccessible.

<a name="pop_front"></a>
### `void Vector<T>::pop_front();`

This is not as trivial as <a href="#pop_back">pop_back</a> as if the internal array is not already empty, we'll need to
perform an in place shift. Even with a full array this is simple though as we'll just be shifting everything down by one.
A simple loop such as

```cpp
for (int i = 1; i < size; ++i) {
  array[i - 1] = array[i];
}
```

captures the necessary logic.

With the first element of the array overwritten, we can decrement our internal size variable.

*Note the above loop is safe as it will only perform on an array with 2 or more elements. This function becomes identical to
<a href="#pop_back">pop_back</a> on arrays with a single element, as it should. Cute huh?

<a name="reverse"></a>
### `void Vector<T>::reverse();`

Exactly how to reverse an array is not terribly relevant to this document.

<a name="brackets"></a>
### `T& Vector<T>::operator[](int i); const`

This function mostly acts as a pass through to index in our internal array with some additional safety like boundary checking and error throwing.

<a name="clear"></a>
### `void Vector<T>::clear();`

This function resets the vector by deleting the internal array. In order to make it correct and safe we must follow our invariants of properly
updating our internal size and capacity variables as well as setting the internal array pointer equal to `NULL` so that multiple calls to
`clear()` do not fail.

*Note clear is called from the destructor so its goal is to ensure that all memory is deleted. Therefore the capacity will always be 0 and
you cannot store anything in the vector after calling `clear()`. I wouldn't mind seeing this change maybe to take in a flag determining whether
the destructor called this as a "final clear" or if this is a user friendly call that keeps the vector usable afterward.
