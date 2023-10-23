#include<unistd.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int create_listenfd(void)
{
	int fd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in sin;
	bzero(&sin,sizeof(sin));
	sin.sin_family=AF_INET;
	sin.sin_port=htons(80);
	sin.sin_addr.s_addr=INADDR_ANY;
	
	int res=bind(fd,(struct sockaddr*)&sin,sizeof(sin));
	if(res==-1)
	{
		perror("bind");
	}

	listen(fd,100);
	return fd;

}


void handle_request(int fd)
{
	char buffer[1024*1024]={0};
	int nread = read(fd,buffer,sizeof(buffer));
	printf("Request income%s\n",buffer);

	char filename[10]={0};
	sscanf(buffer,"GET /%s",filename);
	printf("Filename%\n",filename);

	char *mime=NULL;
	if(strstr(filename,".html"))
	mime="text/html";
	else
	if(strstr(filename,".jpg"))
	mime="image/jpg";



	char response[1024*1024]={0};
	sprintf(response,"HTTP/1.1 200 OK\r\nContent-Type: %s\r\n\r\n",mime);
	int headlen=strlen(response);



	int filefd=open(filename,O_RDONLY);
	int filelen=read(filefd,response+headlen,sizeof(response)-headlen);


	write(fd,response,headlen+filelen);
	close(filefd);
	sleep(1);

}


int main()
{
	int sockfd=create_listenfd();
	int n=1;
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&n,4);

	
	while(1)
	{
	
	int fd=accept(sockfd,NULL,NULL);
	printf("ClientConnecting\n");
		

	handle_request(fd);

	close(fd);
	}

	close(sockfd);

}
