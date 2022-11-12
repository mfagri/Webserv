/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:40:54 by mfagri            #+#    #+#             */
/*   Updated: 2022/11/12 21:53:02 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h>
// #include <in.h>
#include <libc.h>

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
    sockAddress.sin_port = htons(1337);// port
    sockAddress.sin_addr.s_addr = htonl(INADDR_ANY);/////// any incoming IP addres
    // sockAddress.sin_addr.s_addr  = inet_addr("127.0.0.1");

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
    std::cout<<buf<<std::endl;
    //std::string s = buf;
    // char **ss = s.
    memset(buf,0,1024);
    strcpy(buf,"HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 7\n\nMfagri!");
    send(n,buf,1024,0);
}