/* Guy Reuveni 206398596
 * Niv Swisa 208189126
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "ThreadPool/ThreadPool.h"
#include "SyncGraph/graph.h"
#include "ThreadPool/TaskQueue.h"
#include <pthread.h>

typedef struct {
    Graph* graph;
    int startVertex;
    int** m;
    pthread_mutex_t* m_mutexes;
    ThreadPool* pool;
} BFSTaskArgs;

void* bfsTask(void* arg) {
    BFSTaskArgs* args = (BFSTaskArgs*)arg;
    Graph* graph = args->graph;
    int startVertex = args->startVertex;
    int** m = args->m;
    pthread_mutex_t* m_mutexes = args->m_mutexes;

    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = false;
    }

    int* queue = (int*)malloc(graph->numVertices * sizeof(int));
    int front = 0, rear = 0;

    queue[rear++] = startVertex;
    visited[startVertex] = true;
    m[startVertex][startVertex] = 0;

    while (front < rear) {
        int current = queue[front++];

        node* adjList = graph->adjacencyLists[current];
        while (adjList != NULL) {
            int next = adjList->v;

            if (!visited[next]) {
                visited[next] = true;
                queue[rear++] = next;

                pthread_mutex_lock(&m_mutexes[startVertex]);
                m[startVertex][next] = m[startVertex][current] + 1;
                pthread_mutex_unlock(&m_mutexes[startVertex]);
            }

            adjList = adjList->next;
        }
    }
    --(args->pool->runningThreads);
    free(visited);
    free(queue);
    free(args);
    return NULL;
}

void bfs(Graph* graph, int** m) {
    pthread_mutex_t* m_mutexes = (pthread_mutex_t*)malloc(graph->numVertices * sizeof(pthread_mutex_t));
    for (int i = 0; i < graph->numVertices; ++i) {
        pthread_mutex_init(&m_mutexes[i], NULL);
    }

    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            m[i][j] = -1;
        }
    }

    ThreadPool pool;
    pool.maxThreads = 4;
    atomic_init(&pool.runningThreads, 0);
    pool.q = (TaskQueue*)malloc(sizeof(TaskQueue));
    initQueue(pool.q);

    for (int i = 0; i < graph->numVertices; ++i) {
        BFSTaskArgs* args = (BFSTaskArgs*)malloc(sizeof(BFSTaskArgs));
        *args = (BFSTaskArgs){graph, i, m, m_mutexes, &pool};
        TaskData td = {bfsTask, args};
        insert(pool.q, td);
    }

    runThreadPool(&pool);

    for (int i = 0; i < graph->numVertices; ++i) {
        pthread_mutex_destroy(&m_mutexes[i]);
    }
    free(m_mutexes);
}
