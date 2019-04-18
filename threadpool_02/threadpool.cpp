//
// Created by sun on 19-4-18.
//

#include <cassert>
#include "threadpool.h"
threadpool::threadpool(int _threadCounts) {
    threadCounts = _threadCounts;
    shutdown = false;
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&notify,NULL);
    threadpool_create();
}
threadpool::~threadpool(){
    threadpool_destroy();
};

int threadpool::threadpool_create() {
    thread = (pthread_t*)malloc(threadCounts*sizeof(pthread_t));
    for (int i = 0; i < threadCounts; ++i) {
        pthread_create(&thread[i],NULL,threadpool_Fun, static_cast<void*>(this));
    }
    return 0;
}

int threadpool::threadpool_addTask(const Task& task) {
    pthread_mutex_lock(&lock);
    taskQueue.push_back(task);
    pthread_cond_signal(&notify);
    pthread_mutex_unlock(&lock);
    return 0;
}

int threadpool::threadpool_destroy() {
    pthread_mutex_lock(&lock);
    shutdown=true;
    pthread_cond_broadcast(&notify);
    for (int i = 0; i < threadCounts; ++i) {
        pthread_join(thread[i],NULL);
    }
    pthread_mutex_unlock(&lock);
    free(thread);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&notify);
    return 0;
}

void* threadpool::threadpool_Fun(void *arg) {
    threadpool *pool = static_cast<threadpool*>(arg);
    threadpool::Task task = NULL;
    while(1){
        pthread_mutex_lock(&pool->lock);
        while(pool->taskQueue.empty()){
            pthread_cond_wait(&pool->notify,NULL);
        }
        if(pool->shutdown)
            break;
        assert(!pool->taskQueue.empty());
        task = (pool->taskQueue).front();
        pool->taskQueue.pop_front();

        pthread_mutex_unlock(&pool->lock);
        assert(task);
        task();
    }
    pthread_mutex_unlock(&pool->lock);
    pthread_exit(NULL);
    return 0;

}