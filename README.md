# RedBlackTree_C
A simple but working Red Black Tree implementation.

@Before -> Nodes are printed on screen with black and red colors so use a terminal with white background (or whatever you like but not these 2 colors).

If you want to change print colors further informations are avaible in ".h" file within print functions.

The program is very easy to use, just insert numbers. By the way text on console may guide you.

In order to use it follow these steps :

- Open terminal.
- Move to the folder that contains this project.
- Copy paste " gcc *.c -o projectName "
- To execute : " ./projectName "


The structure "node" has 2 sons (left, right) and one more pointer to its parent with key-value and color fields.

Inside this program you will find these functions :

- Read input with validation (only numbers are accepted).
- Insert.
- Rotations.
- 3 violation cases (6 total counting specular cases).
- Fix.
- Print tree (prints a maximum of 8 lines because I tried to build something cool to watch, if you need more feel free to write your own print).

Balancing is ensured by 6 violation cases, no need to check heights.

If you need a "delete node" function you should do it by yourself, just remember that each node has a pointer 
to its parent so you need to update all parent pointers before deleting the node. Then call fix on the new node
that could lead to a violation. This link https://en.wikipedia.org/wiki/Red–black_tree may help but must be revisited.

For any need, feel free to contact me.
