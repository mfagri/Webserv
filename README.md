# Webserv

## **Description**
This project is here to make you write your own HTTP server. You will be able to test it with a real browser. HTTP is one of the most used protocol on internet. Knowing its arcane will be useful, even if you won't be working on a website.


## **what is a server?**

****Server****
 is a software or hardware device that accepts and responds to requests made over a network. The device that makes the request, and receives a response from the server, is called a [client](https://www.computerhope.com/jargon/c/client.htm)
. On the Internet, the term "server" commonly refers to the computer system that receives requests for a web files and sends those files to the client.

## **What are they used for?**

Servers manage [network](https://www.computerhope.com/jargon/n/network.htm) resources. For example, a user may set up a server to control access to a network, send/receive [e-mail](https://www.computerhope.com/jargon/e/email.htm), manage print jobs, or host a [website](https://www.computerhope.com/jargon/w/website.htm). They are also proficient at performing intense calculations. Some servers are committed to a specific task, often referred to as dedicated. However, many servers today are shared servers that take on the responsibility of e-mail, [DNS](https://www.computerhope.com/jargon/d/dns.htm), [FTP](https://www.computerhope.com/jargon/f/ftp.htm), and multiple websites in the case of a web server.

## **Why are servers always on?**

Because they are commonly used to deliver services that are constantly required, most servers are never turned off. Consequently, when servers fail, they can cause the network users and company many problems. To alleviate these issues, servers are commonly set up to be [fault tolerant](https://www.computerhope.com/jargon/f/faulttol.htm).

**how server is work?**

There are two behind-the-scene players that work as partners to get a website to show up on your screen properly: the browser and the web server.When an internet searcher types in a URL, the browser divides the URL into three parts:

- The hypertext transfer protocol: http
- The server name: www.thewebsite.com
- The file name: web-server.htm

Each of these parts have a different responsibility when it comes to interacting with a web server.

### **1. Hypertext Transfer Protocol**

The hypertext transfer protocol (HTTP) is the language browsers and web servers use to communicate. A browser delivers an HTTP request to a web server, and the web server transfers the hypertext to the internet searcher’s browser.When a server receives a request, it checks whether or not the requested URL matches an existing file. If it does, it will speedily return the requested file. If the file does not exist, it will return an error page.

### **2. Domain Name System**

The next part of the equation is the Domain Name System (DNS), which translates easy-to-remember domain names to numerical IP addresses. When you type a domain name into a browser, your internet service provider views the DNS that is tied to the domain name, translates it into a computer-friendly IP address, and then directs your internet connection to the server, delivering up a set of stored files. These stored files show up as a website.

### **3. File Name**

The web server stores all of the data files related to each unique domain name. This includes all the content, HTML documents, images, CSS stylesheets, videos, fonts, JavaScript files, and more — basically, everything that converts into organized text, design, images, or videos when you see a website.And that’s it. Now the next time you surf the web, you’ll know exactly what’s happening behind the curtain. 

**server content?**

It consists of the hardware and software that is responsible for responding to requests on the World Wide Web, with the use of hypertext transfer protocol (HTTP) and other protocols. These requests are made by clients.

# Web Server Architecture

Web server architecture is the layout of a web server. These are developed, designed, and deployed based on the web server architecture. All the essential components of a web server, which are required for delivering web-server-based operations and services, are defined in the architectural layout.

There are certain parameters that are defined in the web server architecture, including:

- The physical capacity of the server. This includes storage, memory, and computing power.
- The quality of the server and its performance. This includes throughput, latency, and low memory use.
- The application tiers. This includes the different types of applications that are deployed on the server.
- The platform that is supported.
- The operating system.
- The network or internet connectivity.

There are two approaches to web server architecture:

- Concurrent Approach
- Single-process-event-driven Approach

### **Concurrent Approach**

With the concurrent approach, a web server can handle multiple client requests at the same time. One of the following three methods can be used to achieve that:

- Multi-process
- Multithreaded
- Hybrid

### **Multi-process**

A single parent process creates various single-threaded child processes and then distributes all the incoming requests to the child processes. All the child processes handle one request at a time. The parent process is responsible for monitoring the load and deciding if a process needs to be forked or filled.

### **Multithreaded**

Multiple single-threaded processes are created to handle various requests.

### **Hybrid**

This approach combines the above two approaches. Multiple processes are created that initiate multiple threads. One thread handles one connection.

### **Single-process-event-driven Approach**

In the single-process-event-driven (SPED) approach, a single process performs all client processing and activity, in an event-driven manner. It uses a single event-driven server process, and is responsible for processing multiple HTTP requests concurrently.

# **Web Server Security**

It is very important to keep your web server secure. With the absence of web server security, your web server is vulnerable to various attacks such as [DoS attacks](https://intellipaat.com/blog/what-is-a-denial-of-service-attack-dos/), SSoS attacks, [SQL injections](https://intellipaat.com/blog/tutorial/ethical-hacking-cyber-security-tutorial/sql-injection-wireless-network-hacking/), unpatched software, cross-site scripting, and much more.

You can protect your web server in the following ways:

- Keep only required services on your server. Having too many services on your web server can open portals. This can enable hacking activities in the long run. An additional benefit of removing unnecessary services is that it will improve the overall website functionality.
- By having separate environments for development, testing, and production, you can reduce the risk of breach. Preferably, separate environments should be kept private.
- Automate backups and install a firewall. A firewall will come in handy even if all your security systems are compromised. By automating backup daily, you can preserve data for the long run. This will be useful even when your system is compromised beyond repair.

## HTTP request

An HTTP request is a message sent by a client to a server to request specific information or resources from the server. HTTP stands for Hypertext Transfer Protocol, and it is the foundation of data communication on the World Wide Web.

HTTP requests consist of a request line, headers, and an optional message body. The request line consists of three parts: the HTTP method, the requested resource, and the HTTP version. The headers contain additional information about the request, such as the type of content being requested or the user agent making the request. The message body, if present, contains the data being sent with the request.

Here is an example of an HTTP request:
```
GET /index.html HTTP/1.1
Host: www.example.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/87.0.4280.141 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
Accept-Encoding: gzip, deflate, br
Accept-Language: en-US,en;q=0.9
```
In this example, the HTTP method is GET, the requested resource is /index.html, and the HTTP version is HTTP/1.1. The headers include information about the host, user agent, accepted content types, and more.

### Request line:
	Request-Line   = Method SP Request-URI SP HTTP-Version CRLF
        Http verb,uri,http version number
### Exemple:

	GET /home.html HTTP/1.1
	POST /index.html HTTP/1.1
	DELETE /query.html HTTP/1.1
	CONNECT
	GET Request - Used when a client is asking a server for some data.
	POST Request - Used when a client wants to send data to a server.
	Ps: if data has been requested , the server will respond by sending the data to the client.
### Request header

Those are just some examples of the HTTP header parameters that you can use. Here’s what each line in that header means:

	Host: This is the IP or URL of the server that you’re making the request to.
	User-agent: This parameter contains information about the client and its Operating System (OS). Typically, this outlines the browser that 	  you’re using and its version.
	Accept-language: This line tells the server what language the client prefers, in case there are multiple versions of the file that you’re 	  requesting.
	Accept-encoding: This line indicates the type of encoding or compression that the client can process.
	Connection: This parameter tells the server whether to keep the connection alive or set a timeout for it. If the connecti
	
### Exemple:

	Host: website.com
 
	User-Agent: Chrome/5.0 (Windows 10)
 
	Accept-Language: en-US
 
	Accept-Encoding: gzip, deflate
 
	Connection: keep-alive</code.


## HTTP response

An HTTP response is a message sent by a server to a client in response to an HTTP request. It consists of a status line, headers, and an optional message body.

The status line consists of three parts: the HTTP version, a status code, and a reason phrase. The status code is a three-digit number that indicates the status of the request. The reason phrase is a brief description of the status code.

Here is an example of an HTTP response:

```
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 348
Date: Mon, 01 Jan 2018 00:00:00 GMT
Connection: keep-alive
```
```html
<html>
<head>
  <title>Example Page</title>
</head>
<body>
  <h1>Hello, world!</h1>
</body>
</html>
```

```

In this example, the HTTP version is HTTP/1.1, the status code is 200, and the reason phrase is OK. The headers include information about the content type, length, date, and connection status. The message body contains the HTML code for the example page.



## CGI 

To create a CGI (Common Gateway Interface) program using C++, you will need to follow these steps:
Write the C++ code for your CGI program. This code should handle the input received from the client (usually through environment variables and standard input) and generate the appropriate output (usually by printing to standard output).

Compile the C++ code into an executable binary. This can be done using a C++ compiler such as g++.
Place the executable binary in the appropriate directory on your web server. This directory is usually called "cgi-bin" or something similar.
Configure your web server to recognize and execute CGI programs. This will typically involve adding a directive to your server's configuration file (such as .htaccess on Apache) to tell the server which directories contain CGI programs, and how to execute them.
Test your CGI program by accessing it through a web browser. The URL for the program will typically be in the form "http://yourserver/cgi-bin/yourprogram".
It's important to note that CGI programs have some inherent security risks, as they allow users to execute arbitrary code on your server. It's important to carefully review and secure your CGI programs to ensure that they do not allow unauthorized access or compromise the security of your server.




In the Common Gateway Interface (CGI) protocol, environment variables are used to pass information from the web server to the CGI program. They can contain information such as the client's IP address, the requested URL, the query string, and various other pieces of information.
Here is a list of some common environment variables that may be set by the web server when executing a CGI program:

	QUERY_STRING: The query string from the URL, if any.
	REQUEST_METHOD: The HTTP method used to request the CGI program (e.g. "GET", "POST", etc.)
	CONTENT_TYPE: The MIME type of the request body, if any.
	CONTENT_LENGTH: The length of the request body, if any.
	HTTP_USER_AGENT: The user agent string from the client's browser.
	HTTP_REFERER: The URL of the page that referred the client to the CGI program.
	REMOTE_ADDR: The IP address of the client.
	SERVER_NAME: The hostname of the server.
	SERVER_SOFTWARE: The name and version of the web server software.

These environment variables can be accessed by the CGI program through the standard C library function getenv.
It's important to note that environment variables are not a secure way to pass sensitive information, as they can be easily manipulated by malicious clients. For this reason, they should not be used to pass sensitive data such as passwords or other confidential information.

### My CGI code:

```cpp
std::string	get_cgistring(FILE *temp, int fdtemp)
{
	char buff[4096];
	std::string string;

    rewind(temp);
	while(!feof(temp))
 	{
       if (fgets(buff, 4096, temp) == NULL)
             break;
       string += buff;
 	}
	close(fdtemp);
	fclose(temp);
    return (string);
}

std::string launch_cgi(std::string path,std::string bin ,Request &Req)
{
	std::string			cgistring;
    char *arg[3];
    arg[0] = strdup(bin.c_str()); //pass cgi
    arg[1] = strdup(path.c_str());//path file// char *g = "sdsdsff";
    arg[2] = NULL;
    
    std::map<std::string,std::string> reqheaders = Req.get_headers();
    std::string query = Req.get_queryuri();
    
    std::map<std::string ,std::string > env;
    env["SERVER_NAME"] ="webserv";
    env["HTTP_USER_AGENT"] = reqheaders["User-Agent"];
    env["SERVER_PROTOCOL"] = "HTTP/1.1";
    env["GATEWAY_INTERFACE"] = "CGI/1.1";
    env["REDIRECT_STATUS"] = "200";
    env["PATH_INFO"] = path;
    env["PATH_TRANSLATED"] = path;
    env["SERVER_PORT"] = reqheaders["Host"].substr(reqheaders["Host"].find(":")+1).c_str();//need host
    env["REQUEST_METHOD"] = Req.get_methode();
    env["REQUEST_URI"] = Req.get_uri();
    env["HTTP_HOST"] = reqheaders["Host"];
    env["SCRIPT_NAME"] = Req.get_uri();
    env["SCRIPT_FILENAME"] = path;
    env["CONTENT_TYPE"] = reqheaders["Content-Type"];
    if (reqheaders.count("Cookie"))
    {
       env["HTTP_COOKIE"] = reqheaders.at("Cookie");
    }
    if(Req.get_methode() == "POST")
    {
        env["CONTENT_LENGTH"] = reqheaders["Content-Length"];
    }
    else{
        if(!query.empty())
        {
            env["QUERY_STRING"] = query;
            env["CONTENT_LENGTH"] = "0";
        }
    }
    FILE		*temp = std::tmpfile();
    FILE		*tempo = std::tmpfile();
    int			fdtemp = fileno(temp);
    int			fdtempo = fileno(tempo);
    std::string data ;
    

    std::map<std::string, std::string>::iterator it;
    for (it = env.begin(); it != env.end(); ++it) {
        setenv(it->first.c_str() ,it->second.c_str(), 1);
    }
    int f = fork();
    extern char **environ;
    if(Req.get_methode() == "POST")
    {
        if(dup2(fdtempo,0) < 0)
            std::cout<<"errro\n";
        std::string s = Req.get_body_req();
        s = s.substr(s.find("\r\n\r\n")+4);
        write(fdtempo,s.c_str(),s.length());
        rewind(tempo);
    }
    if(f == 0)
    {
        if(dup2(fdtemp, 1) < 0)
            std::cout<<"errro\n";
        execve(arg[0],arg,environ);
        exit(0);
    }
    else
    {
        waitpid(-1,NULL,0);
        cgistring = get_cgistring(temp,fdtemp);
    }
    free(arg[0]);
    free(arg[1]);
    unsetenv("QUERY_STRING");
    return (cgistring);
}
```
