# Mthreadpool
## threadpool_01
将threadpool用类封装起来，类中定义了任务队列和线程数组，用函数指针的方式实现函数的多态，这里注意到一个问题：当用类内部的函数指针指向成员函数时，会出现编译错误，将成员函数定义成静态成员函数即可，这就是threadpool_thread 是static的原因。但是static函数没有this指针，必须传入this指针才能访问到类中的私有成员变量。
[类内部指针指向成员函数错误解析](https://blog.csdn.net/maojudong/article/details/8194143 "悬停显示")
