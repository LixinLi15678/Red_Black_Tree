# Red Black Tree

I implemented a red black tree in Python. It is a self-balancing binary search tree. It is a binary search tree that has the following properties:

1. Every node is either red or black.
2. The root is black.
3. Every leaf (NIL) is black.
4. If a node is red, then both its children are black.
5. For each node, all simple paths from the node to descendant leaves contain the same number of black nodes.

The worst case running time for search, insert, and delete is O(log n).