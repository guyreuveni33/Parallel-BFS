# Guy Reuveni 206398596
# Niv Swisa 208189126

# Target executable name
TARGET = part_III.out

# Source files
SRCS = main.c bfs.c SyncGraph/graph.c ThreadPool/TaskQueue.c ThreadPool/ThreadPool.c

# Compiler and flags
CC = gcc
# CFLAGS = place flags if needed
# Default target builds the executable
$(TARGET): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) -o $@

# Clean target removes the executable
clean:
	rm -f $(TARGET)

