# Data_structures and algorithms
Here's written in C++ implementations of data structures such as a binary search tree (which named just as tree), an avl-tree, a linked list (disordered), a hash-map and a graph and algorithms such as a merge sort and a heap sort.

In the graph's implementation I wrote implementations of the DFS and the BFS algorithms and algorithms based on DFS and BFS such as defining the shortest path, calculating a number of components, bipartion of a graph, defining articulation vertices, topological sorting and defining strongly connected components.

Every implementation of the structures uses an iterative approach in order to avoid excessive calls of function, though a recursive method is more intuitive especially for trees.

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
