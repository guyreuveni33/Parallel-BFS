/* Guy Reuveni 206398596
 * Niv Swisa 208189126
*/

#ifndef BFS_H
#define BFS_H

#include "SyncGraph/graph.h" // Assuming this is where `Graph` is defined
#include "ThreadPool/ThreadPool.h" // Assuming this contains `ThreadPool` definitions

#ifdef __cplusplus
extern "C" {
#endif

// Forward declaration of the struct if not defined elsewhere
struct BFSTaskArgs;

// Declaration of the bfs function
void bfs(Graph* graph, int** m);

#ifdef __cplusplus
}
#endif

#endif // BFS_H
