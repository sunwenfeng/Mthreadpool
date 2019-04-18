#include <iostream>
#include <unistd.h>
#include "threadpool.h"

class Task1{
public:
    Task1(){}
    int run(int i,const char* p){
        cout<<pthread_self()<<" exec Task1 "<<" runs "<<i<<" "<<p<<endl;
        sleep(1);
        return 0;
    }
};
class Task2{
public:
    Task2(){}
    int run(int a,int b,const char* p){
        cout<<pthread_self()<<" exec Task2 "<<" runs "<<a+b<<" "<<p<<endl;
        sleep(1);
        return 0;
    }
};

int main()
{
    threadpool threadPool(10);
    Task1 task1[10];
    for(int i = 0; i < 10; i++)
    {
        threadPool.threadpool_addTask(std::bind(&Task1::run, &task1[i], i, "hello task1"));//两个参数：int 和 char* ，返回值int
    }
    Task2 task2[10];
    for(int i=0;i<10;i++){
        threadPool.threadpool_addTask(std::bind(&Task2::run, &task2[i], i,100, "hello task2"));//两个参数：int 和 char* ，返回值int
    }

    while(1)
    {
        printf("there are still %d tasks need to process\n", threadPool.size());
        if (threadPool.size() == 0)
        {
            threadPool.threadpool_destroy();
            printf("Now I will exit from main\n");
            exit(0);
        }
        sleep(2);
    }

    return 0;
}
