# Crystal-Kingdom-Game

Given a starting point and the destination of a randomly generated crystal, the program finds the Minimum Spanning Tree and Shortest Path using Floyd, Prim, Kruskal and Dijkstra Algorithms.

Project Overview:

This C++ project focuses on finding the Minimum Spanning Tree and Shortest Path in a graph. Given a starting point and the destination of a randomly generated crystal, the program employs various algorithms, including Floyd, Prim, Kruskal, and Dijkstra, to determine the optimal routes. The project utilizes fundamental data structures and algorithms to accomplish these tasks efficiently.

Features: The project includes the following features:

Minimum Spanning Tree (MST): The program finds the MST of a given graph using two popular algorithms:

Prim's Algorithm: It constructs the MST by starting from an initial vertex and greedily adding the shortest edge that connects the current tree to a non-tree vertex. Kruskal's Algorithm: It builds the MST by iteratively adding the shortest edge that does not form a cycle in the current tree. Shortest Path: The program calculates the shortest path between a starting point and a destination vertex in the graph. Two algorithms are implemented:

Dijkstra's Algorithm: It computes the shortest path from the source vertex to all other vertices by iteratively selecting the vertex with the minimum distance. Floyd-Warshall Algorithm: It determines the shortest paths between all pairs of vertices in the graph by considering all intermediate vertices. Randomly Generated Graph: The project generates a random graph with crystals as vertices. Each crystal represents a unique location, and the edges represent the distances between them.

Score Calculation: The program utilizes an AVL tree to calculate scores based on various parameters. The AVL tree is a self-balancing binary search tree that efficiently maintains sorted data, allowing for quick score retrieval and updates.

Data Structures Concepts: The project demonstrates the implementation and usage of the following data structures concepts:

Graph: A graph is represented using adjacency matrix or adjacency list, facilitating the storage and manipulation of vertex and edge information.

Heap: A binary heap is used in Prim's Algorithm to efficiently select the minimum edge during MST construction.

Disjoint Set: A disjoint set data structure is employed in Kruskal's Algorithm to detect and merge disjoint sets efficiently.

AVL Tree: The AVL tree data structure is utilized for score calculation, providing efficient search, insertion, and deletion operations.

Getting Started: To run the project, follow these steps:

Clone the repository: git clone <repository_url>

Compile the source code: g++ main.cpp -o main

Run the program: ./main

Follow the on-screen instructions to input the starting point and destination of the crystal.

Contributing: Contributions are welcome! If you encounter any issues or have suggestions for improvement, please open an issue or submit a pull request.

Acknowledgements: I would like to thank the contributors and developers, Usman Nazeer and Bilal Saleem who have worked on the algorithms and data structures implemented in this project. Their efforts and contributions have made this project possible.
