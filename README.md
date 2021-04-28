# RedBlackTree_C
A simple but working Red Black Tree implementation.

The program is very easy to use, just insert numbers. By the way text on console may guide you.

The structure "node" has 2 childrean (left, right) and one more pointer to its parent with key-value fields.

Inside this program you will find these functions :

- Read input with validation (only numbers are accepted).
- Insert.
- Rotations.
- 3 violation cases (6 total counting specular cases).
- Print tree (prints a maximum of 8 lines because I tried to build something cool to watch, if you need more feel free to write your own print).

Balancing is ensured by 6 violation cases, no need to check heights.

If you need a "delete node" function you should do it by yourself, just remember that each node has a pointer 
to its parent so you need to update all parent pointers before deleting the node. Then call fix on the new node
that could lead to a violation. This (link)[https://en.wikipedia.org/wiki/Red–black_tree] may help but must be revisited.

For any need, feel free to contact me.
