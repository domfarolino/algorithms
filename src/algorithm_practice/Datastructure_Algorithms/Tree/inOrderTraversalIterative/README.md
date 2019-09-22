# In Order Traversal (Iterative)

Source:

 - https://leetcode.com/problems/binary-tree-inorder-traversal/description/

Performing an inorder traversal on a binary tree recursively is trivial, but
a more interesting version of this is doing it iteratively. We know that all
*recursion can be simulated with a stack*, so let's figure out how we can
approach this problem with a stack.

Example:

```
         3
       /   \
      5     4
     / \   / \
    1  9  8   7

correct inorder traversal: [1, 5, 9, 3, 8, 4, 7]
```

Since an inorder traversal must first "visit" the left-most node in the tree,
we know that our algorithm must simulate recursing left immediately. Recursion
is naturally performed by pushing values on a stack (in stack frames), so that
when the recursion unwinds, previous values can be re-visited in the reverse
order that they were pushed. We can "simulate" recursing down the left-subtree
of a given node by iterating down the left subtree of a node as far as we can,
pushing each node to a stack for later use. We do this until we cannot get any
further.

```
stack:
[1] (top)
[5]
[3] (bottom)
---------------

         3
       /   \
      5     x
     / \
    1  x
```

At some point, we'll no longer be able to iterate any further down the left
subtree, and the current node will be null. In this case, we can simulate
unwinding our recursion by popping a value from the stack (`1`) and considering
this to be our "current root".

When we pop a node from the stack, we know we've exhausted its left subtree,
so we can continue the inorder traversal like so:

1. "Visit" the node
  1. In this case, just push the node's value to the back of a vector
1. Recurse down the right subtree

When we "recurse" down the right subtree, we simply set the "current root" to the
"current root"'s right child and start our algorithm over from the new "current root".
There are two possible cases:

1. The "current root" is non-null
  1. Typical case. Algorithm restarts, attempting to iterate down the left subtree
1. The "current root" is null
  1. This is valid. Algorithm restarts, and cannot iterate down the left subtree anymore.
     We then pop from the stack, and run the visiting steps on the closest un-visted parent.

Only when the "current root" is null and we don't have any unvisted parents in the stack to
"unwind" to, the entire tree has been fully exhausted. Beautiful.

<!--
TODO(domfarolino): Consider explaining my original approach, though it is a bit lengthy
My first
approach to this problem was to dump the root (if non-null) into the stack
immediately, and keep operating on the stack while there were elements in it.

When we examine the non-empty stack, the `top` node will be the current root
we're interested in. Just like the recursive solution, we want to first simulate
recursing on the left tree of the `top`-most node. To do this, we'll take the
top-most node, keep it in the stack, and push its left child to the stack so we
can visit this subtree. We'll keep doing this until the left-most child does not
have a subtree, in which case our "recursion" bottoms out.

```
stack:
[1] (top)
[5]
[3] (bottom)

current root = 1 (no children!)
```

When we're considering the node `1`, we cannot go left anymore. As an inorder
traversal mandates, we'll "visit" this node, and then consider the right subtree.
In this case there is no right subtree, so we can simply simulate unwinding our
recursing by popping the top-most node in the stack, and attempting to visit it.

```
stack:
[5] (top)
[3] (bottom)

current root = 5
```

Next we consider the top-most node `5`, but we need to make sure we don't simply
repeat the left-subtree-traversal steps on `5` again. So what could we have done
earlier to mark the progress we've made on `5` so that when we encounter it again
in the stack, we choose to visit it and consider its right subtree, instead of visit
its left subtree _again_? The approach I came up with was to dump it into another stack
exclusively for nodes that:

 - We've started to visit the left subtree for
 - But we haven't visited themselves, or their right subtree yet

It then became clear to me that the first stack would only ever have one node in it
at a time, in which case we could substitute it for a simple node pointer.

...
-->

# Complexity analysis

 - Time complexity: O(n)
 - Space complexity: O(n)
