# Data_structures
Here's implementations of data structures written in C++ such as a binary search tree (which named just as tree), an avl-tree, a linked list(disordered) and a hash-map.

Every implementation of the structures use an iterative approach in order to avoid excessive calls of function, though a recursive method is more intuitive especially
for trees.

Descriptions of mentioned structres you can find everywhere in the Web, so I only notice to the time complexity in big O notation:
1. BS tree: Average case   Worst case
      
       - Space : O(n)       O(n) 
       - Search: O(log n)   O(n)
       - Insert: O(log n)   O(n)
       - Delete: O(log n)   O(n)

2.  AVL tree: Average case  Worst case
    
        - Space : O(n)          O(n)
        - Search: O(log n)      O(log n)
        - Insert: O(log n)      O(log n)
        - Delete: O(log n)      O(log n)
  
 3. Linked list: Average case  Worst case 
        
        - Space:  O(n)          O(n)  
        - Search: O(n)          O(n)
        - Insert: O(1)          O(1)
        - Delete: O(1)          O(1)
 
 4. Hash-map: Average case Worst case
     
        - Space:  O(n)          O(n)  
        - Search: O(1)          O(n)
        - Insert: O(1)          O(n)
        - Delete: O(1)          O(n)
