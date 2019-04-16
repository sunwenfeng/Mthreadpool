//
// Created by sun on 19-4-15.
//

#include <cstdlib>
#include <iostream>
#include "threadpool.h"

threadpool::threadpool(int _threadCount, int _queueSize) {
    threadCount = _threadCount;
    queueSize = _queueSize;
    head = 0;
    tail = 0;
    waitExecTasks = 0;
    shutdown = false;
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&notify, NULL);
    threadpool_create();
}
threadpool::~threadpool() {
    threadpool_destroy();
}


int threadpool::threadpool_create() {//创建线程池
    if(threadCount < 0 || queueSize < 0)
        return threadpool_invalidSize;

    thread = (pthread_t*)malloc(threadCount*sizeof(pthread_t *));
    taskQueue = (task_t*)malloc(queueSize*sizeof(task_t*));
    if(thread == NULL || taskQueue == NULL)
        return threadpool_invalidMalloc;

    for (int i = 0; i < threadCount; ++i) {
        //if(pthread_create(&thread[i], NULL,threadpool_thread, this) !=0)
            //return threadpool_invalidCreatethread;
        pthread_create(&thread[i], NULL,threadpool_thread, this);
    }
    return 0;
}
int threadpool::threadpool_add(void (*fun)(void*),void* arg) {//向线程池中添加任务
    if(fun == NULL)
        return threadpool_invalidTask;

    if(pthread_mutex_lock(&lock)!=0)
        return threadpool_failLock;

    int next = (tail+1) % queueSize;

    if(waitExecTasks == queueSize)
        return threadpool_fullQueue;

    if(shutdown)
        return threadpool_poolShutdown;

    //std::cout<<tail<<std::endl;

    if(tail<0 || tail >=queueSize)
        std::cout<<tail<<" outbound"<<std::endl;

    taskQueue[tail].fun = fun;
    taskQueue[tail].argument = arg;
    tail=next;
    waitExecTasks++;

    //std::cout<<"df"<<std::endl;

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
    std::cout<<"exec task"<<std::endl;
    while(1){
        pthread_mutex_lock(&(pool->lock));

        while(pool->waitExecTasks==0 && !pool->shutdown){
            //std::cout<<"waitExecTasks: "<<pool->waitExecTasks<<std::endl;
            pthread_cond_wait(&(pool->notify),&(pool->lock));
        }

        if(pool->shutdown)
            break;


        task.fun = pool->taskQueue[pool->head].fun;
        task.argument = pool->taskQueue[pool->head].argument;
        pool->head = (pool->head+1)%pool->queueSize;
        pool->waitExecTasks--;

        pthread_mutex_unlock(&pool->lock);

        (*(task.fun))(task.argument);
        std::cout<<"left: "<<pool->waitExecTasks<<std::endl;

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
    free(taskQueue);//???这行出错，问题未知
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&notify);

    return 0;
}