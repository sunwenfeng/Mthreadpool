//
// Created by sun on 19-4-15.
//

#ifndef THREADPOOL_01_THREADPOOL_H
#define THREADPOOL_01_THREADPOOL_H

#include <pthread.h>
#include <deque>
#include <thread_db.h>

/*线程池第一版，将threadpool写成封装成类，用函数指针的方式实现函数多态
 * */
typedef struct task{
    void(*fun)(void*);
    void* argument;
}task_t;

enum threadpool_error{
    threadpool_invalidSize          =   -1,
    threadpool_invalidMalloc        =   -2,
    threadpool_invalidCreatethread  =   -3,
    threadpool_fullQueue            =   -4,
    threadpool_invalidTask          =   -5,
    threadpool_failLock             =   -6,
    threadpool_poolShutdown         =   -7
};

class threadpool {
public:
    threadpool(int _threadCount,int _ququeSize);//call create
    ~threadpool();//call threadpool_free

    int threadpool_create();
    int threadpool_add(void (*fun)(void*),void* arg);
    int threadpool_destroy();
    int size(){return waitExecTasks;}
private:
    pthread_mutex_t lock;       //条件变量互斥锁
    pthread_cond_t notify;      //条件变量用于等待
    pthread_t *thread;          //线程数组
    task_t *taskQueue;          //任务队列数组
    int threadCount;
    int queueSize;
    int head;
    int tail;
    bool shutdown;
    int waitExecTasks;                  //待运行的任务

    static void* threadpool_thread(void *threadArg);
    //类内部的函数指针指向成员函数时会编译错误，指向静态成员函数是可以的，但静态成员函数没有this指针，传入this指针即可
};


#endif //THREADPOOL_01_THREADPOOL_H
