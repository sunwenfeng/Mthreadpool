//
// Created by sun on 19-4-18.
//

#ifndef THREADPOOL_02_THREADPOOL_H
#define THREADPOOL_02_THREADPOOL_H


#include <pthread.h>
#include <functional>
#include <deque>

using namespace std;

class threadpool {
    /*
     * 线程池第二版，用function和bind实现回调函数，将每个任务封装成一个函数对象
     * */
public:
    typedef function<void()> Task;

    threadpool(int _threadCounts=10);
    ~threadpool();

    int threadpool_create();
    int threadpool_addTask (const Task& task);
    int threadpool_destroy();
    int size(){ return taskQueue.size();}
private:
    threadpool& operator=(const threadpool&) const;
    threadpool(const threadpool&);

    static void* threadpool_Fun(void *arg);

    pthread_t * thread;
    deque<Task> taskQueue;
    int threadCounts;       //总线程数量
    bool shutdown;

    pthread_mutex_t lock;
    pthread_cond_t notify;

};


#endif //THREADPOOL_02_THREADPOOL_H
