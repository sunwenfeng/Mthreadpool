# Mthreadpool
## threadpool_01
将threadpool用类封装起来，类中定义了任务队列和线程数组，用函数指针的方式实现回调函数，这里注意到一个问题：当用类内部的函数指针指向成员函数时，会出现编译错误，将成员函数定义成静态成员函数即可，这就是threadpool_thread 是static的原因。但是static函数没有this指针，必须传入this指针才能访问到类中的私有成员变量。

[类内部指针指向成员函数错误解析](https://blog.csdn.net/maojudong/article/details/8194143 "悬停显示")

## threadpool_02
使用function和bind实现回调函数。将任务抽象成类，类中实现run方法，将类中的run方法通过bind绑定到function对象并执行。
这里注意到一个问题：
function<void()>对象可以接受任意参数的函数,这样线程池就可以接受不同参数的任务。在main()的测试中，可以把int run(int i,const char*p) 和 int run(int a,int b,const char*p)两种函数bind之后传给function<void()>;

关于fuction和bind的学习，在文档threadpool.docx
