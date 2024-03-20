# Parallel-BFS Implementation 

## Overview

This README accompanies the second assignment for the "Parallel Systems Programming" course (תכנות מערכות מקביליות), focusing on the implementation of a parallel Breadth-First Search (BFS) algorithm for undirected graphs. This implementation calculates the shortest path matrix for the given graph, employing thread pooling to achieve parallelism.

## Files Description

- `bfs.c` & `bfs.h`: Contains the parallel BFS algorithm implementation and its header file, respectively. The `bfs` function updates the shortest path matrix for the given graph.

- `graph.c` & `graph.h`: Defines the graph structure and basic operations such as adding edges and creating the graph. These are essential for representing the input graph.

- `ThreadPool.c` & `ThreadPool.h`: Implements a thread pool for managing multiple threads that perform the BFS task in parallel, including task queuing and execution.

- `TaskQueue.c` & `TaskQueue.h`: Provides functionality for a task queue used within the thread pool to store tasks awaiting execution.

- `main.c`: The main driver program that reads graph input, invokes the BFS function, and prints the shortest path matrix.

- `makefile`: Defines the build instructions for compiling the source code. 

## Compilation and Execution

### Cloning the Repository

First, clone the repository that contains the BFS implementation and related files. Open your terminal and run:

```sh
git clone https://github.com/guyreuveni33/Parallel-BFS.git
```

### Navigating to the Project Directory

Change to the directory of the cloned project:

```sh
cd Parallel-BFS
```

### Compilation Using the Provided Makefile

Given the makefile details, compile the project with the following command in the terminal:

```sh
make
```

### Running the BFS Program

After compilation, run the generated executable using input redirection from a file for ease of testing:

```sh
./part_III.out
```
