# Webserv
http Webserv


**what is a server?**

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
