/* Guy Reuveni 206398596
 * Niv Swisa 208189126
*/

#include "ThreadPool.h"
#include "TaskQueue.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
//this is the ThreadPool from tirgul 5 that was uploaded to the moodle.
void runThreadPool(ThreadPool *tp) {
    int thread_count = 0;
    /* As long as there are tasks in the queue or running threads... */
    while (!isEmpty(tp->q) || tp->runningThreads > 0) {
        /* If we are not past max number of threads */
        if (tp->runningThreads < tp->maxThreads && !isEmpty(tp->q)) {
            /* Run task */
            TaskData data = pop(tp->q);

            pthread_t thread;
            if (pthread_create(&thread, NULL, data.function, data.args)) {
                perror("pthread_create failed.");
                exit(1);
            } else {
                ++(tp->runningThreads);
            }
        }
    }
}