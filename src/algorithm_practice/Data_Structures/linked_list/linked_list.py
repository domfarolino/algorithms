"""
A singly-linked list implementation in Python (2.7).

O(1) for insertion. 
O(N) for deletion/search/size.

Advantages
 - Dynamic data structure (allocates memory at runtime.)
 - Insertion is quick.
 - Easy to implement.

Disadvantages
 - Linked lists use more memory.
 - Sequential data access.

"""

class Node:
    def __init__(self, data, _next):
        self.data = data
        self._next = _next

class LinkedList:
    def __init__(self):
        self.head = None
        self.tail = None

    def show(self):
        node = self.head
        if not node:
            print None
            return
        while node:
            print node.data,
            if node._next:
                print "=>",
            node = node._next
        print ""
        
    def append(self, data): 
        node = Node(data, None)
        if self.head is None:
            self.head = node
        else:
            self.tail._next = node
        self.tail = node

    def remove(self, data):
        node = self.head
        prevNode = None
        while node:
            if node.data == data:
                if prevNode:
                    prevNode._next = node._next
                else:
                    self.head = node._next
                return
            prevNode = node
            node = node._next
    
    def size(self):
        node = self.head
        size = 0
        while node:
            size = size + 1
            node = node._next
        return size

    def search(self, data):
        node = self.head
        while node:
            if node.data == data:
                return True
            node = node._next
        return False

# Usage

s = LinkedList()

print "size", s.size()

s.append(10)
s.append("Sausage")
s.append(12.5)

print "size", s.size()

s.show()

print "Contains 'Sausage'", s.search("Sausage")

s.remove("Sausage")

print "size", s.size()

s.show()
s.remove(10)

print "Contains 'Sausage'", s.search("Sausage")

s.show()

