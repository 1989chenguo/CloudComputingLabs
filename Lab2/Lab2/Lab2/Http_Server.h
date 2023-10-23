#ifndef _HTTPSERVER_H_
#define _HTTPSERVER_H_
#include <iostream>
#include<cstring>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/wait.h>
using namespace std;


#define BUFFER_SIZE 4096
class  HttpServer{
    private:
        int socketfd;
    public:
        HttpServer(){}
        HttpServer(int id):socketfd(id){}
        ~HttpServer(){}
        void dealHttp();
		void deal_get(string url,string method);//处理get请求
        void deal_post(string name,string id);//处理post请求
        void Not_Implemented(string method);//非post,get请求
        void Not_Found(string url,string method);//文件未找到
        
};

#endif
