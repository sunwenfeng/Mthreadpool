//
// Created by sun on 19-4-15.
//

#ifndef THREADPOOL_01_THREADPOOL_H
#define THREADPOOL_01_THREADPOOL_H

#include <pthread.h>
#include <deque>
#include <thread_db.h>
using namespace std;

/*线程池第一版，将threadpool写成封装成类，用函数指针的方式实现函数多态，实现思路同threadpool
 * */
typedef struct task{
    void(*fun)(void*);
    void* argument;
}task_t;

enum threadpool_error{
    threadpool_invalidSize          =   -1,
    threadpool_invalidMalloc        =   -2,
    threadpool_invalidCreatethread  =   -3,
    threadpool_invalidTask          =   -4,
    threadpool_failLock             =   -5,
    threadpool_poolShutdown         =   -6
};

class threadpool {
public:
    threadpool(int _threadCount);   //call create
    ~threadpool();                  //call threadpool_free

    int threadpool_create();
    int threadpool_add(void (*fun)(void*),void* arg);
    int threadpool_destroy();
    int size(){return taskQueue.size();}
private:
    pthread_mutex_t lock;       //条件变量互斥锁
    pthread_cond_t notify;      //条件变量用于等待
    pthread_t *thread;          //线程数组
    deque<task_t> taskQueue;    //deque中存放的是待运行的任务，添加任务时到队列尾部，从头部取任务运行
    int threadCount;
    bool shutdown;

    static void* threadpool_thread(void *threadArg);
    //类内部的函数指针指向成员函数时会编译错误，指向静态成员函数是可以的，但静态成员函数没有this指针，传入this指针即可
};


#endif //THREADPOOL_01_THREADPOOL_H
