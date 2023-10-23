#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <pthread.h>
#include <queue>
#include "Http_Server.h"
#include <exception>
using namespace std;

class Thread_Pool{
    private:
        pthread_mutex_t lock;    
        pthread_cond_t cond;  
        queue<HttpServer> task_queue;
        int thread_count; //线程数
        vector<pthread_t> thread;  //线程池中的线程
    
    public:

        Thread_Pool(int num):thread_count(num){
            pthread_mutex_init(&lock,NULL);
            cond = PTHREAD_COND_INITIALIZER;
            thread=vector<pthread_t>(thread_count);
        }

        ~Thread_Pool(){
            pthread_mutex_destroy(&lock);
            pthread_cond_destroy(&cond);
        }
        void initPool();//构建线程池

        void queue_Add(HttpServer t);//向工作队列中加入请求
        void queue_Pop();//消费工作队列中的请求

        static void* work(void *arg);//所有子线程创建完成后，子线程才开始运行
};

#endif
