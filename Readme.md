LinusListix folder contains the original doubly-linked list in LinusListix.h, but it contains many excessive functions and didn't have the node class within the main class, so...
the folder Listix contains the less-bulky, better organized, all-in-one doubly-linked list with selector pointer. The selector pointer remembers the last-accessed node so that when you access the list again, it can reach the next location fast without iterating from the beginning. It will shoot straight to the beginning or the end of the list via the head and tail pointers if it is faster to access your desired location from there.

LinusListix folder also contains a quadratic hash table, a 64-bit index version of the original LinuxListix, and a string based on the class.
