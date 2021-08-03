Marvel Universe Graph
===

Application of basic graph algorithms in Java. The exact problem specifications can be found in the [statement](https://github.com/pshrey795/Graph-Algorithms/blob/main/MarvelGraph/Statement.pdf). The input files (node file and edge file) construct the graph required.

How to compile the files?
---

1. Type `javac A4_2019CS10400.java` to compile the main file.
2. In the console, we can perform three operations, for which first type `java A4_2019CS10400 <input_node_file> <input_edge_file>` followed by the name of the function which you want to perform:

  * **average:** To find the average number of Marvel characters that each character is associated with, i.e. average degree of all nodes.
  * **rank:** To print a sorted list of all characters(exact specifications in the [statement](https://github.com/pshrey795/Graph-Algorithms/blob/main/MarvelGraph/Statement.pdf)).
  * **independant storylines dfs**: To find the number of independent storylines in the graph i.e. the number of connected components.
