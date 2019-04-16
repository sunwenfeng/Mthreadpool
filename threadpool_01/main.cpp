#include <iostream>
#include <zconf.h>
#include "threadpool.h"
using namespace std;

void taskTest(void *arg){
    sleep(1);
    cout<<pthread_self()<<" runs task " << *(static_cast<int*>(arg))<<endl;
}

int main() {

    threadpool pool(3,10);//3 thread,10 task
    for(int i=0;i<10;i++){
        sleep(1);
        pool.threadpool_add(taskTest,&i);
    }
    while(1){
        if(pool.size()==0){
            sleep(3);
            pool.threadpool_destroy();
            cout<<"exit"<<endl;
            break;
        }
        sleep(2);
    }
    cout<<"hello"<<endl;
    return 0;
}