//
// Created by sun on 19-4-15.
//

/*#ifndef THREADPOOL_01_TASK_H
#define THREADPOOL_01_TASK_H

#include <string>
#include <iostream>

using namespace std;

class task {
public:
    task(string _taskname="",void* _arg=NULL):taskname(_taskname),arg(_arg){}
    virtual ~task(){}
    virtual void run()=0;
protected:
    string taskname;
    void* arg;//only can accept one arg
};

class first_task:public task{
    first_task(string& _taskname,void* _arg=NULL):task(_taskname,_arg){}
    void run() {
        cout << pthread_self() << " runing and arg is " << static_cast<char *>(arg);
    }

};
#endif //THREADPOOL_01_TASK_H
*/