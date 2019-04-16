//
// Created by sun on 19-4-15.
//

#include <cstdlib>
#include <iostream>
#include "threadpool.h"

threadpool::threadpool(int _threadCount) {
    threadCount = _threadCount;
    shutdown = false;
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&notify, NULL);
    threadpool_create();
}
threadpool::~threadpool() {
    threadpool_destroy();
}


int threadpool::threadpool_create() {//创建线程池
    if(threadCount < 0)
        return threadpool_invalidSize;

    thread = (pthread_t*)malloc(threadCount*sizeof(pthread_t *));
    if(thread == NULL)
        return threadpool_invalidMalloc;

    for (int i = 0; i < threadCount; ++i) {
        if(pthread_create(&thread[i], NULL,threadpool_thread, this) !=0)
            return threadpool_invalidCreatethread;
    }
    return 0;
}
int threadpool::threadpool_add(void (*fun)(void*),void* arg) {//向线程池中添加任务
    if(fun == NULL)
        return threadpool_invalidTask;

    if(pthread_mutex_lock(&lock)!=0)
        return threadpool_failLock;

    if(shutdown)
        return threadpool_poolShutdown;

    task_t task;
    task.fun = fun;
    task.argument = arg;
    taskQueue.push_back(task);

    if(pthread_cond_signal(&notify)!=0)
        return threadpool_failLock;
    if(pthread_mutex_unlock(&lock)!=0)
        return threadpool_failLock;

    return 0;

}


void* threadpool::threadpool_thread(void *threadArg) {//执行任务，静态函数，需要传入this指针
    //threadpool_thread传入的是this指针
    task_t task;
    threadpool* pool = static_cast<threadpool*>(threadArg);

    while(1){
        pthread_mutex_lock(&(pool->lock));

        while(pool->taskQueue.size() == 0 && !pool->shutdown){
            pthread_cond_wait(&(pool->notify),&(pool->lock));
            std::cout<<"awake"<<std::endl;
        }

        if(pool->shutdown)
        {
            std::cout<<"shutdown"<<std::endl;
            break;
        }

        task.fun = (pool->taskQueue.front()).fun;
        task.argument = (pool->taskQueue.front()).argument;

        pool->taskQueue.pop_front();

        pthread_mutex_unlock(&pool->lock);

        (*(task.fun))(task.argument);
    }
    pthread_mutex_unlock(&(pool->lock));
    pthread_exit(NULL);
}

int threadpool::threadpool_destroy() {//销毁线程池

    if(pthread_mutex_lock(&lock)!=0)
        return threadpool_failLock;

    shutdown=true;

    if(pthread_cond_broadcast(&notify)!=0)
        return threadpool_failLock;
    if(pthread_mutex_unlock(&lock))
        return threadpool_failLock;

    for(int i=0;i<threadCount;i++)
        pthread_join(thread[i], NULL);

    free(thread);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&notify);

    return 0;
}