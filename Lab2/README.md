# Lab2:Your Own HTTP Server

Enter in the folder you have cloned from our lab git repo, and pull the latest commit. 

`git pull`

You can find this lab2's instruction in `Lab2/README.md` 

All materials of lab2 are in folder `Lab2/`

## 1. Overview

Implement a HTTP server from scratch. Use high concurrency strategy to guarantee the web server performance.

## 2. Background

### 2.1 Hypertext Transport Protocol

The Hypertext Transport Protocol (HTTP) is the most commonly used application protocol on the Internet today. Like many network protocols, HTTP uses a client-server model. An HTTP client opens a network connection to an HTTP server and sends an HTTP request message. Then, the server replies with an HTTP response message, which usually contains some resource (file, text, binary data) that was requested by the client.

### 2.2 HTTP Messages

HTTP messages are simple, formatted blocks of data. All HTTP messages fall into two types: request messages and response messages. Request messages request an action from a web server. Response messages carry results of a request back to a client. Both request and response messages have the same basic message structure.

#### 2.2.1 The Parts of a Message 

HTTP messages consist of 3 parts: a start line describing the message, a block of headers containing attributes, and an optional body containing data.

##### 2.2.1.1 Start Lines

All HTTP messages begin with a start line. The start line for a request message says *what to do*. The
start line for a response message says *what happened*.

Specifically, the start line is also called *Request line* in *Request messages* and *Response line* in *Response messages*.

1. **Request line:** The request line contains a method describing what operation the server should perform and a request URL describing the resource on which to perform the method. The request line also includes an HTTP version tells the server what dialect of HTTP the client is speaking. All of these fields are separated by whitespace.

Example of request line:

`GET /index.html HTTP/1.0`

2. **Response line:** The response line contains the HTTP version that the response message is using, a numeric status code, and a textual reason phrase describing the status of the operation.

Example of response line:

`HTTP/1.0 200 OK`

##### 2.2.1.2 Headers

Following the start line comes a list of zero, one, or many HTTP header fields. HTTP header fields add additional information to request and response messages. They are basically just lists of name/value pairs. Each HTTP header has a simple syntax: a name, followed by a colon (:), followed by optional whitespace, followed by the field value, followed by a CRLF.

HTTP headers are classified into: General headers, Request headers, Response headers, Entity headers and Extension headers. 

Example of headers:

```
Host: 127.0.0.1:8888
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:74.0) Gecko/20100101 Firefox/74.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Upgrade-Insecure-Requests: 1
Cache-Control: max-age=0
								     // CRLF
```

##### 2.2.1.3 Entity Bodies

The third part of an HTTP message is the optional entity body. Entity bodies are the payload of HTTP messages. They are the things that HTTP was designed to transport.

HTTP messages can carry many kinds of digital data: images, video, HTML documents, software applications, credit card transactions, electronic mail, and so on.

Example of entity body:

```
<html><head>
<title>CS06142</title>
</head><body>
<h1>CS06142</h1>
<p>Welcome to Cloud Computing Course.<br />
</p>
<hr>
<address>Http Server at ip-127-0-0-1 Port 8888</address>
</body></html>
```

#### 2.2.2 Structure of HTTP Request

A HTTP request message contains an HTTP request line (containing a method, a query string, and the HTTP protocol version), zero or more HTTP header lines and a blank line (i.e. a CRLF by itself).

 Example of HTTP request message:

```
GET /index.html HTTP/1.0   
Host: 127.0.0.1:8888
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:74.0) Gecko/20100101 Firefox/74.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Upgrade-Insecure-Requests: 1
Cache-Control: max-age=0
								     // CRLF
```

#### 2.2.3 Structure of HTTP Response

A HTTP response message contains an HTTP response status line (containing the HTTP protocol version, the status code, and a description of the status code), zero or more HTTP header lines, a blank line (i.e. a CRLF by itself) and the content requested by the HTTP request.

Example of HTTP response message:

```
HTTP/1.0 200 OK  					
Server: Tiny Web Server
Content-length: 248
Content-type: text/html
									// CRLF
<html><head>
<title>CS06142</title>
</head><body>
<h1>CS06142</h1>
<p>Welcome to Cloud Computing Course.<br />
</p>
<hr>
<address>Http Server at ip-127-0-0-1 Port 8888</address>
</body></html>
```

### 2.3 HTTP Proxy

HTTP proxy servers are intermediaries. Proxies sit between clients and servers and act as "middlemen", shuffling HTTP messages back and forth between the parties.

HTTP proxy servers are middlemen that fulfill transactions on the client's behalf. Without a HTTP proxy, HTTP clients talk directly to HTTP servers. With a HTTP proxy, the client instead talks to the proxy, which itself communicates with the server on the client's behalf.

HTTP proxy servers are both web servers and web clients. Because HTTP clients send request messages to proxies, the proxy server must properly handle the requests and the connections and return responses, just like a web server. At the same time, the proxy itself sends requests to servers, so it must also behave like a correct HTTP client, sending requests and receiving responses.

 The working pattern of HTTP proxy:

```
                               +-----------+               +-----------+
                               |           |               |           |
   +----------+    Request     |           |   Request     |           |
   |          |+--------------->           |+-------------->           |
   |  Client  |                |   Proxy   |               |   Server  |
   |          <---------------+|           <--------------+|           |          
   +----------+	   Response    |           |   Response    |           |          
                               |           |               |           |
                               +-----------+               +-----------+
```

## 3. Your Lab Task

### 3.1 Build your own HTTP Server

In this Lab, we won't provide any basic code. So, you should implement a HTTP server from scratch which satisfies the following requirements:

#### 3.1.1 HTTP Server Outline

From a network standpoint, your HTTP server should implement the following:

1. Create a listening socket and bind it to a port
2. Wait a client to connect to the port
3. Accept the client and obtain a new connection socket
4. Read in and parse the HTTP request
5. Start delivering services: 1) Handle HTTP GET/POST request and return an error message if an error occur.
                              2) Proxy the request to another HTTP server.(optional)

The server will be in either non-proxy mode or proxy mode (we have introduced the proxy in session `2.3`). It does not do both things at the same time.

#### 3.1.2 Handle HTTP request

In this Lab, you just need to implement the GET method and the POST method in your HTTP server. That is to say, if your HTTP server receive a HTTP request but the request method is neithor GET nor POST. The HTTP server just need to return a 501 Not Implemented error message.

##### 3.1.2.1 Handle HTTP GET request

The HTTP server should be able to handle HTTP GET requests for files. 

1. For the convenience of TAs testing. You must put a html file (please name it `index.html`) in server root directory.

2. If the HTTP request’s path corresponds to a file, respond with a 200 OK and the full contents
of the file. (e.g. if GET /index.html is requested, and a file named index.html exists in the
files directory) You should also be able to handle requests to files in subdirectories of the files
directory (e.g. GET /images/hero.jpg). 

3. If the HTTP request’s path corresponds to a directory and the directory contains an `index.html`
file, respond with a 200 OK and the full contents of the index.html file.

4. If the request corresponds to a directory and the directory does not contain an `index.html`
file, return a 404 Not Found response (the HTTP body is optional).

5. Otherwise, return a 404 Not Found response (the HTTP body is optional). 

##### 3.1.2.2 Handle HTTP POST request

The HTTP server should be able to handle HTTP POST requests. In this lab, the way of handle HTTP POST is much simple. 

1. You should construct a HTTP POST request (see session `3.1.7.2`) that contains 2 keys: "Name" and "ID" (please fill in your name and student number respectively), and send the POST request to `/Post_show` (i.e. `http://127.0.0.1:8888/Post_show` if server's IP is `127.0.0.1` and service port is `8888`).

Then, if the HTTP server receive this POST request (the request URL is `/Post_show` and the keys are "Name" and "ID"), respond with a 200 OK and echo key-value pairs you have sent. (see session `3.1.7.2`).

2. Otherwise (i.e. the request URL is not `/Post_show` or the keys are not "Name" and "ID"), return a 404 Not Found response message. 

##### 3.1.2.3 Other request

Just return 501 Not Implemented error message for other request method (e.g. DELETE, PUT, etc. see session `3.1.7.3`).

#### 3.1.3 Use thread pool

You should use a fixed-sized thread pool in your HTTP server program for handling multiple client request concurrently.

1. The main idea of the thread pool is threads reuse. In short summary, the thread pool contains a set of threads:

If there are no tasks, those threads are in a waiting state.

If a new task comes, assign an idle thread to the new task.

If all threads in the thread pool are in busy state, the new task will be placed in a waiting queue or add a new thread to process the task.

2. Your thread pool should be able to concurrently serve exactly --num-threads clients and no
more. Note that you can use --num-threads + 1 threads in your program: the original thread is responsible for accept()-ing client connections in a while loop and dispatching the associated requests to be handled by the threads in the thread pool.

3. Hints: 

Read the man pages for `pthread_cond_init ()` and `pthread_mutex_init ()`. You may need these synchronization primitives.

#### 3.1.4 Implement a proxy server

Enable your server to proxy HTTP requests to another HTTP server and forward the responses to the clients.

1. You should use the value of the --proxy command line argument, which contains the address and port number of the upstream HTTP server.

2. Your proxy server should wait for new data on both sockets (the HTTP client fd, and the upstream HTTP server fd). When data arrives, you should immediately read it to a buffer and then write it to the other socket. You are essentially maintaining 2-way communication between the HTTP client and the upstream HTTP server. Note that your proxy must support multiple requests/responses.

3. If either of the sockets closes, communication cannot continue, so you should close the other socket and exit the child process.

4. Hints:

 1) This is more tricky than writing to a file or reading from stdin, since you do not know which side of the 2-way stream will write data first, or whether they will write more data after receiving a response. In proxy mode, you will find that multiple HTTP request/responses are sent within the same connection, unlike your HTTP server which only needs to support one request/response per connection.

 2) You should again use pthreads for this task. Consider using two threads to facilitate the two-way communication, one from A to B and the other from B to A. It is ok to use multiple threads to serve a single client proxy request, as long as your implementation can still only serve exactly --num-threads clients and no more.

 3) Use those functions carefully: select(), fcntl(), or the like. Those methods could be confusing.

#### 3.1.5 Specify arguments

Your program should enable long options to accept arguments and specify those arguments during start. They are "--ip", "--port", "--number-thread" and "--proxy"(optional).
  
1. --ip&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;&ensp; —— Specify the server IP address.
2. --port&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;&ensp; —— Selects which port the HTTP server listens on for incoming connections.
3. --number-thread —— Indicates the number of threads in your thread pool that are able to concurrently server client requests. This argument is initially unused and it is up to you to use it properly.
4. --proxy&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;&ensp; —— Selects an “upstream” HTTP server to proxy. The argument can have a port number after a colon (e.g. `https://www.CS06142.com:80`). If a port number is not specified, port 80 is the default.

If you have no idea about *long options*, you can read [this](https://www.gnu.org/software/libc/manual/html_node/Argument-Syntax.html#Argument-Syntax). And you may need to use some functions like `getopt_long ()`, `getopt_long_only ()`, `getopt ()` and so on. Check those function's usage with the `man` command.

#### 3.1.6 Run your HTTP Server

Your program should be able to start at terminal. If your program is called *httpserver*, just typing:

in the non-proxy mode: 

`./httpserver --ip 127.0.0.1 --port 8888 --number-thread 8` 

It means that your HTTP server's IP address is 127.0.0.1 and service port is 8888. The --number-thread indicates that there are 8 threads in the thread pool for handling multiple client request concurrently.

in the proxy mode:

`./httpserver --ip 127.0.0.1 --port 8888 --number-thread 8 --proxy https://www.CS06142.com:80`

It means that this is a HTTP proxy. This proxy's IP address is 127.0.0.1 and service port is 8888. And the proxy has a thread pool with 8 threads. The --proxy indicates that the "upstream" HTTP server is `https://www.CS06142.COM:80`. So, if you send a request message to this proxy (i.e. `127.0.0.1:8888`), it will forward this request message to the "upstream" HTTP server (i.e. `https://www.CS06142.com:80`) and forward the response message to the client.

When you run the command above, your HTTP server should run correctly.

#### 3.1.7 Accessing Your HTTP Server

##### 3.1.7.1 Using GET method

1. You can check that your HTTP server works by opening your web browser and going to the appropriate URL.

  For example:

<img src="src/index.png" alt="index page" title="index page" style="zoom:43%;" />


2. You can also send HTTP requests with the curl program. An example of how to use curl is:

`curl -X GET http://127.0.0.1:8888/index.html`

  For example:

<img src="src/index_curl.png" alt="index page curl" title="index page curl" style="zoom:50%;" />

3. If the request page is non-existent, your HTTP server should return a 404 Not Found error message.

##### 3.1.7.2 Using POST method

1. You can check whether the POST method works by sending a HTTP request with the curl program. Typing the command at terminal:

`curl -X POST --data 'Name=HNU&ID=CS06142' http://127.0.0.1:8888/Post_show`

  For example:

<img src="src/post_curl.png" alt="post curl" title="post curl" style="zoom:50%;" />

2. You can also construct a POST HTTP request and send the request to Http Server by means of browser plug-in.

##### 3.1.7.3 Other method

The HTTP server will not handle HTTP requests expect GET requests and POST requests.

If you send a HTTP DELETE (or PUT, HEAD, etc.) request to delete the specified resource, you will get a 501 Not Implemented error message:

<img src="src/not_implemented_curl.png" alt="Not implemented" title="Not implemented" style="zoom:50%;" />

#### 3.1.8 Implementation requirements

##### 3.1.8.1 Basic version

Your program should be able to:

1. Enable to handle HTTP GET requests and HTTP POST requests.

2. Return an appropriate error message if an error occur (e.g. 404 Not Found, 501 Not Implemented). 

3. Using a fixed-sized thread pool for handling multiple client request concurrently.

\[Tips\]: 1) Dynamically detect how many CPU cores are there on your machine, in order to decide how many threads 
should be in the thread pool.

##### 3.1.8.2 Advanced version

Your program should be able to:

1. Complete all the requirements in the basic version.

2. Enable to proxy HTTP requests to another HTTP server.

3. Use *epoll* instead of thread pool to enable your proxy to support multiple requests/responses.

### 3.2 Finish a performance test report
Please test your code first, and commit a test report along with your lab code into your group’s course github repo.

The test report should describe your test inputs, and the performance result under various testing conditions. Specifically, in your test report, you should at least contain the following two things:


## 4. Lab submission

Please put all your code in folder `Lab2` and write a `Makefile` so that we **can compile your code in one single command** `make`. The compiled runnable executable binary should be named `httpserver` and located in folder `Lab2`. Please carefully following above rules so that TAs can automatically test your code!!!

Please submit your lab program and performance test report following the guidance in the [Overall Lab Instructions](../README.md) (`../README.md`)

## 5. Grading standards

1. You can get 38 points if you can: 1) finish all the requirements of the basic version, and 2) your performance test report has finished the two requirements described before. If you missed some parts, you will get part of the points depending how much you finished
2. You can get 40 points (full score) if you can: 1) finish all the requirements of the advanced version, and 2) your performance test report has finished the two requirements described before. If you missed some parts, you will get part of the points depending how much you finished.