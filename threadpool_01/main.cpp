#include <iostream>
#include <zconf.h>
#include "threadpool.h"
using namespace std;

//int done=0,tasks=0;
pthread_mutex_t lock;
void taskTest(void *arg){
    sleep(1);
    cout<<pthread_self()<<" runs task " << *(static_cast<int*>(arg))<<endl<<endl;
}

int main() {

    threadpool pool(3);//3 thread
    for(int i=0;i<10;i++){
        pool.threadpool_add(taskTest,&i);
        sleep(2);
    }
    /*while(1){
        if(pool.size()==0){
            sleep(2);
            pool.threadpool_destroy();
            cout<<"exit"<<endl;
            break;
        }
    }*/

    //析构函数释放内存

    return 0;
}