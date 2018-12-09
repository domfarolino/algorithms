# Serialize and Deserialize a Binary Tree

Source:

 - Interview question
 - https://leetcode.com/problems/serialize-and-deserialize-binary-tree/description/

The idea for this algorithm and task is to create a serialization and deserialization
scheme/format for binary trees. You must serialize a binary tree into a string which
can be of any format as long as calling the deserialize algorithm on said string produces
a binary tree identical the one that was serialized. The serialization must be stateless.
You can imagine this would be useful to serialize a data structure into a string for storage
or network transport, and deserialize on the receiving side. You can assume your deserialization
algorithm will only be called with valid serialized strings.

Performing this task requires answering the following question: In what way can I capture all of
the information that perfectly describes a binary tree? The information is of course the nodes, and
their relationship to one another. Traversals give us all of this information, so let's explore how
we can use a few.

# Naive & BFS

We can of course have a really trivial serialization scheme that essentially prints the tree out in
level-order form, for all possible levels. Consider the following tree:

```
       1
      /
     2
      \
       3
```

A level-order traversal string for this tree would be "123". This is ambiguous though, and since we
can have many trees with this same traversal, we'll have to find a way to represent absent nodes. A
naive approach to this would be to simply pretend the tree were perfect, and have "null" or something
similar representing absent nodes. This is trivial, but for anything more sparse than a perfect binary
tree (completely full at all levels), it is incredibly wasteful. The final serialization would have
(2<sup>h</sup>) - 1 members, where _h_ is the height of the tree.

Alternatively we could be a little more smart and not put a ton of useless unreachable "null"s in places,
and could only place "null" in places where the first null node. This would be a lot more efficient. We
could basically do BFS, and instead of not pushing null children to our queue, we could allow them and handle
them separately to influence our serialized string only where necessary.

This is an easy serialization method using BFS, and we can do something similar for deserialization. How can
we rebuild a tree from its BFS traversal (with "null" spacers added in where necessary)? Consider the following
traversal string: "1,2,3,null,null,7,8". Intuitively we can probably see that this is the following tree:

```
   1
  / \
 2   3
    / \
   7   8
```

...but how can we get to this in code? We'll want to grab the first node value from the string. We know
that the following two will be its children. We'll have to maintain a queue of nodes we get from the string
so that we can build the tree back up in typical BFS fashion. We'll set 1's children to 2 and 3, and queue them.
2 will be at the head of the queue, so let's grab it; we see that the next two values are "null". In this case,
we do nothing, remove 2 from the queue, and move on. 3 is at the head of the queue. The next two values, its
children, are 7 and 8. Since they are non-null, we'll make nodes out of them, and set these nodes to the left
and right children of 3. We'll remove 3 from the queue. Now later we'll want to build 7 and 8's subtrees respectively,
so we'll queue them as well. This will keep the correct order of everything; we just have to make sure that we set
a paren'ts left and right children before we lose a reference to said parent.

Once all's said and done, we'll return the root that we started with, and we'll have an identical tree. Dealing with
separators such as ","s are important, since the numbers that represent a node's value may be longer than one serialized
character, but that is more coding agility than algorithmic prowess.

# DFS approach

I gravitated towards solving this problem by using a DFS traversal. [Preorder](https://en.wikipedia.org/wiki/Tree_traversal#Pre-order_(NLR))
made sense when serializing, as "visiting" a node is essentially committing it to the string, and of course we come
across a node before its children. Also this will make deserializing pretty simple. The idea is pretty similar to the
BFS traversal, however I came at it a bit differently. I first observed the ambiguity created by just simply committing
node values encountered during a preorder traversal to a string. My solution to this ambiguity was to mark when a right
subtree's serialization started.

In other words, a serialized string for a tree would be of the form "N-----R-----", where N's left subtree would occupy
the first space, 'R' would represent the break between subtrees, and the right subtree would occupy the second space. This
could be maintained recursively. Whenever multiple 'R's appeared next to each other, this would simply mean that no right
subtree existed, and whenever a node's value came right before an 'R', we know that there wa no left-subtree. Serialization
is relatively trivial. Deserialization pseudocode is as follows:

```
In: string (str), index reference (i)
Out: Tree node

1. Create a node _node_ that we'll eventually return
2. If i == str.size() return _node_
3. If str[i] != 'R'
  a. Set _node_'s value to the value starting at str[i]
  b. Increment i enough to get past the value we just consumed
  c. Set _node_'s left subtree = recursingnew node whose value is the number at the current pos in the string
  d. newNode->left = deserialize(str, i)
  e. newNode->right = deserialize(str, i)
4. Otherwise i++
5. Return _node_
```

# Complexity analysis

 - Time complexity: O(n)
 - Space complexity: O(n)
