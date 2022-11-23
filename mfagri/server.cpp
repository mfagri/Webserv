/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:40:54 by mfagri            #+#    #+#             */
/*   Updated: 2022/11/23 08:46:52 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>	   //close
#include <arpa/inet.h> //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <vector>
#include <map>
#include <fstream>

#include <sstream>
// #include <in.h>
// #include <libc.h>
#include "request.hpp"

#define PORT 80
/////////////////////////////////
//Application Layer/////////////
////////////////////////////////
//sockets programming
//
//socket descriptor
//socket(domain,type,protocol);
//
//domain (family):
//
//  AF_UNIX
//
//  AF_INET
//
//  AF_INET6
//
//
//////////////////////////////
//
//type:
//
//  SOCK_STREAM -> TCP (Transmision Control Protocol)
//     - reliable byte-stream channel  
//     - connection-oriented
//     - bidirectional
//
//  SOCk_DGRAM -> UDP (User Datagram Protocol)
//     - out of order , duplicates possible
//     - connectionless (faster)
//
//////////////////////////////
//
//
// send(int fd,const void * buf,size_t n,int flag);
// recv(int fd,const void * buf,size_t n,int flag);
//
//
// fd : the socket descriptor.
// buf: array of characters to hold the msg
// n : lenght of buf
// flags: usually 0 (MSG_EOR,MSG_OOB)
//
//
//
//

///////////////////////////////
//Transport Layer/////////////
//////////////////////////////

//////////////////////////////
//Internet Layer/////////////
/////////////////////////////

///////////////////////////////
//Network Access Layer////////
//////////////////////////////

int main()
{
    std::cout<<"mfagri server\n";
    char **t;
    int socketfd;
    struct sockaddr_in sockAddress,cl;// in internet
    
    socketfd = socket(AF_INET,SOCK_STREAM,0);

    if(socketfd < 0)
    {
        std::cout<<"error\n";
        return(1);
    }
    memset(&sockAddress,0,sizeof(sockAddress)); // intit to 0
    sockAddress.sin_family = AF_INET; //define domine
    sockAddress.sin_port = htons(PORT);// port
    //sockAddress.sin_addr.s_addr = htonl(INADDR_ANY);/////// any incoming IP addres
    sockAddress.sin_addr.s_addr  = inet_addr("0.0.0.0");

    if(bind(socketfd,(struct sockaddr *)&sockAddress,sizeof(sockAddress)) < 0)
    {
        std::cout<<"bind error\n";
        return(1);
    }
    
    if(listen(socketfd,10) < 0)
    {
        std::cout<<"error\n";
        return(1);
    }
    else
        std::cout<<"listen.......\n";
    unsigned int len = sizeof(cl);
    int n = accept(socketfd,(struct sockaddr *)&cl, &len);
    if(n < 0)
    {
        std::cout<<"no accept\n";
        return (0);
    }
    else
        std::cout<<"hi client\n";

    char buf[1024];
    recv(n,buf,1024,0);
    
    // t = ft_split(buf,'\n');
    Request a(buf);
    puts("khraj");
    std::string sss;
    if(a.get_status_code() == 200)
        sss = "ok.html";
    else
        sss = "not_found.html";
    std::ifstream f(sss.c_str());
    std::string str;
    std::ostringstream ss;
    ss << f.rdbuf(); // reading data
    str = ss.str();
    //std::cout<<str<<std::endl;
    memset(buf,0,1024);
    strcpy(buf,"HTTP/1.1 ");
    strcat(buf,ft_itoa(a.get_status_code()));
    strcat(buf," OK\nContent-Type: text/html\nContent-Length: "); //9\n\n"
    int lenght;
    lenght = str.length();
    //std::cout<<"lenght:"<<lenght<<std::endl;
    std::string v = ft_itoa(lenght);
    std::string final = v+"\n\n"+str;
    strcat(buf,final.c_str());
    send(n,buf,1024,0);
    printf("response sended\n");
    // while (1);  
}