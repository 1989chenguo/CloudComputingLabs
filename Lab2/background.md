## 2. Background

### 2.1 Hypertext Transport Protocol

The Hypertext Transport Protocol (HTTP) is the most commonly used application protocol on the Internet today. 

Like many network protocols, HTTP uses a client-server model. An HTTP client opens a network connection to an HTTP server and sends an HTTP request message. Then, the server replies with an HTTP response message, which usually contains some resource (file, text, binary data) that was requested by the client. 

We briefly introduce the HTTP message format and structure in this section for your convenience. Detailed specification of HTTP/1.1 can be found in [RFC 2616 - Hypertext Transfer Protocol -- HTTP/1.1](https://tools.ietf.org/html/rfc2616).

### 2.2 HTTP Messages

HTTP messages are simple, formatted blocks of data. 

All HTTP messages fall into two types: **request** messages and **response** messages. 

* Request messages request an action from a web server. 

* Response messages carry results of a request back to a client. 

Both request and response messages have the same basic message structure.

#### 2.2.1 Message Format 

HTTP request and response messages consist of 3 components: 

- a start line describing the message, 
- a block of headers containing attributes, 
- and an optional body containing data.

Each component has the format as following

##### 2.2.1.1 Start Line

All HTTP messages begin with a start line. The start line for a request message says *what to do*. The start line for a response message says *what happened*.

Specifically, the start line is also called ***Request line*** in *Request messages* and ***Response line*** in *Response messages*.

* **Request line** 
   * contains a method describing what operation the server should perform and a request URL describing the resource on which to perform the method. 
   * also includes an HTTP version tells the server what dialect of HTTP the client is speaking. All of these fields are separated by whitespace.
   * eg. `GET /index.html HTTP/1.1`

* **Response line** 
  * contains the HTTP version that the response message is using, a numeric status code, and a textual reason phrase describing the status of the operation.
  *  eg. `HTTP/1.1 200 OK`

##### 2.2.1.2 Header

Following the start line comes a list of zero, one, or many HTTP header fields. 

HTTP header fields add additional information to request and response messages. They are basically just lists of name/value pairs. 

Each HTTP header has a simple syntax: a name, followed by a colon `:`, followed by optional whitespace, followed by the field value, followed by a `CRLF`.

HTTP headers are classified into: 
 * General headers
 * Request headers
 * Response headers
 * Entity headers 
 * Extension headers. 

Note that request-header fields are different from the response-header fields. We will not introduce those fields in details and you are not required to implement in this lab. 

You can find them in [RFC 2616 - Hypertext Transfer Protocol -- HTTP/1.1](https://tools.ietf.org/html/rfc2616).

Example of headers in a request:

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

Example of headers in a response:

```
Server: Guo's Web Server
Content-length: 248
Content-type: text/html
							            // CRLF
```

##### 2.2.1.3 Entity Body

The third part of an HTTP message is the optional entity body. Entity bodies are the payload of HTTP messages. They are the things that HTTP was designed to transmit.

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

A HTTP request message contains:

* an HTTP request line:
  * method,
  * a query string,
  * the HTTP protocol version,
* zero or more HTTP header lines,
* a blank line (i.e. a `CRLF` by itself),
* a optional content that request need to carry.

Example of HTTP request message:

```
GET /index.html HTTP/1.1   
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

A HTTP response message contains:

* an HTTP response status line:
  * the HTTP protocol version,
  * the status code
  * a description of the status code),
* zero or more HTTP header lines,
*  a blank line (i.e. a `CRLF` by itself) 
*  the content requested by the HTTP request.

Example of HTTP response message:

```
HTTP/1.1 200 OK  					
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

The `Host` request header specifies the host and port number of the server to which the request is being sent. If no port is included, the default port for the service requested is implied (e.g., 443 for an HTTPS URL, and 80 for an HTTP URL).

The `Content-Length` header indicates the size of the message body, in bytes, sent to the recipient.

The `Content-Type` representation header is used to indicate the original media type of the resource.

Here are some examples:

| file extension | MIME Type |
| --- | --- |
| *.html | text/html |
| *.js | text/javascript |
| *.css| text/css |
| *.txt | text/plain |
| *.json | application/json |
| *.png | image/png |
| *.jpg | image/jpg |

### 2.3 HTTP Proxy

HTTP proxy servers are intermediaries. Proxies sit between clients and servers and act as "middlemen", shuffling HTTP messages back and forth between the parties.

HTTP proxy servers are middlemen that fulfill transactions on the client's behalf. Without a HTTP proxy, HTTP clients talk directly to HTTP servers. With a HTTP proxy, the client instead talks to the proxy, which itself communicates with the server on the client's behalf.

HTTP proxy servers are both web servers and web clients. Because HTTP clients send request messages to proxies, the proxy server must properly handle the requests and the connections and return responses, just like a web server. At the same time, the proxy itself sends requests to servers, so it must also behave like a correct HTTP client, sending requests and receiving responses.

The working pattern of HTTP proxy is shown in the following figure:

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

## 2.4 JSON

JSON (JavaScript Object Notation) is a lightweight data-interchange format. It is easy for humans to read and write. It is easy for machines to parse and generate. It is based on a subset of the JavaScript Programming Language Standard ECMA-262 3rd Edition - December 1999. JSON is a text format that is completely language independent but uses conventions that are familiar to programmers of the C-family of languages, including C, C++, C#, Java, JavaScript, Perl, Python, and many others. These properties make JSON an ideal data-interchange language.

JSON is built on two structures:

* A collection of name/value pairs. In various languages, this is realized as an object, record, struct, dictionary, hash table, keyed list, or associative array.

* An ordered list of values. In most languages, this is realized as an array, vector, list, or sequence.

These are universal data structures. Virtually all modern programming languages support them in one form or another. It makes sense that a data format that is interchangeable with programming languages also be based on these structures.

In JSON, they take on these forms:

* An object is an unordered set of name/value pairs. An object begins with `{` and ends with `}`. Each name is followed by `:`and the name/value pairs are separated by `,`.

* An array is an ordered collection of values. An array begins with `[` and ends with `]`. Values are separated by `,`.

* A value can be a string in double quotes, or a number, or true or false or null, or an object or an array. These structures can be nested.

* A string is a sequence of zero or more Unicode characters, wrapped in double quotes, using backslash escapes. A character is represented as a single character string. A string is very much like a C or Java string.

* A number is very much like a C or Java number, except that the octal and hexadecimal formats are not used.

* Whitespace can be inserted between any pair of tokens. Excepting a few encoding details, that completely describes the language.

For example:

```json
{
    "status": {
        "code": 200,
        "text": "OK"
    },
    "data" : [
        {
            "id": "S1",
            "name": "Foo"
        },
        "Bar\r\n",
        5.0,
        true,
        null
    ]
}
```

## 2.5 CURL

`curl` is a tool to transfer data from or to a server, using one of the supported protocols (DICT, FILE, FTP, FTPS, GOPHER, HTTP, HTTPS, IMAP, IMAPS, LDAP, LDAPS, MQTT, POP3, POP3S, RTMP, RTMPS, RTSP, SCP, SFTP, SMB, SMBS, SMTP, SMTPS, TELNET and TFTP). The command is designed to work without user interaction.

`curl` offers a busload of useful tricks like proxy support, user authentication, FTP upload, HTTP post, SSL connections, cookies, file transfer resume, Metalink, and more. As you will see below, the number of features will make your head spin!

`curl` is powered by libcurl for all transfer-related features. See libcurl(3) for details.

### 2.5.1 source code

You can check out the latest [source code](https://github.com/curl/curl) from GitHub.

### 2.5.2 install

On many operating systems, curl is already installed by default. If not, you can use the system's package management tool to install it. E.g., `sudo apt install curl` for Ubuntu.

### 2.5.3 tutorials

For more tutorials, please check [curl tutorial](https://curl.se/docs/manual.html) or use `man curl` after installing.

Here we give some examples that you might need in your lab.

#### 2.5.3.1 GET

##### access static resouces

```shell
curl -i -X GET http://localhost:8080/index.html
```

##### access a web service

```shell
curl -i -X GET http://localhost:8080/api/search
```

###### with query string

```shell
curl -i -G -d 'id=1&name=Foo' -X GET http://localhost:8080/api/search
```

##### 2.5.3.2 POST

##### send data like html <form />

```shell
curl -i -d 'id=1&name=Foo'
    -H 'Content-Type: application/x-www-form-urlencoded'
    -X POST http://localhost:8080/api/upload
```

##### send data use form-data

```shell
curl -i -F "id=1" -F "name=Foo"
    -X POST http://localhost:8080/api/upload
```
##### send data use json

```shell
curl -i -d '{"id":"1","name":"Foo"}'
    -H 'Content-Type: application/json'
    -X POST http://localhost:8080/api/upload
```
