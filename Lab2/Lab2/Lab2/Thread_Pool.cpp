#include "Thread_Pool.h"
//创建并启动线程池
void Thread_Pool::initPool(){
    pthread_mutex_lock(&lock);
    for(int i=0;i<thread_count;i++){
        while(pthread_create(&thread[i],NULL,work,this)!=0);
        if(pthread_detach(thread[i])){
            throw std::exception();
        }
    }
    pthread_mutex_unlock(&lock);

}

void* Thread_Pool::work(void* arg){
    Thread_Pool* pool=(Thread_Pool*) arg;
    pool->queue_Pop();
    return NULL;
}

void Thread_Pool::queue_Pop(){
    while(1){
        pthread_mutex_lock(&lock);
        while(task_queue.empty()){
            pthread_cond_wait(&cond,&lock);
        }
        HttpServer http=task_queue.front();
        task_queue.pop();
        
        pthread_mutex_unlock(&lock);
        http.dealHttp();
    }
}

void Thread_Pool::queue_Add(HttpServer task){
    pthread_mutex_lock(&lock);
    task_queue.push(task);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
}

