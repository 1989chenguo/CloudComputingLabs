#include "Http_Server.h"
#include "Thread_Pool.h"

using namespace std;

static int thread_count=20;
int main(int argc, char *argv[])
{//输入不符合规范
	if(argc <5){
		printf("usage : %s --ip   --port  [--number-thread]\n", argv[0]);
		return 1;
    }
	
	//设置服务器ip地址
    string ip=argv[2];
	//设置服务器应用port
    int port = atoi(argv[4]);  
    if(argc==7&&strcmp(argv[5],"--number-thread")==0)
	thread_count=atoi(argv[6]);
    
    int socketfd, connectfd; //服务套接字和连接套接字
	
   	struct sockaddr_in ServerAddr, client;
    //设置服务端的sockaddr_in
    memset(&ServerAddr,0,sizeof(ServerAddr));
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_port = htons(port);
    ServerAddr.sin_addr.s_addr = inet_addr(ip.c_str());
	
	
    //创建设置socket,TCP,IPv4网络
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd < 0){
		printf("socket error\n");
		return 1;
    }
   
    int option=1;
    socklen_t optlen=sizeof(option);
    setsockopt(socketfd,SOL_SOCKET,SO_REUSEADDR,(void*)&option,optlen);
	
   
    int ret = bind(socketfd, (struct sockaddr *)&ServerAddr, sizeof(ServerAddr));
    if(ret < 0){
		printf("Bind error\n");
		return 1;
    }

    
    ret = listen(socketfd, 20);
    if(ret < 0){
		printf("Listen Error\n");
		return 1;
    }

    //创建线程池,默认20个线程
    Thread_Pool pool(thread_count);
    pool.initPool();  //初始化线程池，启动服务器

    while(1){
      socklen_t len = sizeof(client);
      //接受连接
      connectfd = accept(socketfd, (struct sockaddr *)&client, &len);
      if(connectfd!=-1){
        HttpServer task(connectfd);
        //向线程池添加任务
        pool.queue_Add(task);
      }
    }
    close(socketfd);
    return 0;
}
