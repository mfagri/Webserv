/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:06:24 by mfagri            #+#    #+#             */
/*   Updated: 2022/11/16 02:36:23 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request.hpp"
#include <string>
#include <string.h>
/// methods// post | get | delete | connect | put

int find_important_request(char **t,std::string s,int size)
{
    int i;
    i = 0;
    while(t[i])
        if(strncmp(t[i],s.c_str(),size) == 0)
            return (i);
    return (404);
}
Request::Request()
{
    
};

Request::Request(char *buf)
{
    int table_index[6];
    //choise six element i my request 
    std::string the_six_request[6] = {"GET","Host:","User-Agent:","Accept-Language:","Accept-Encoding:","Connection:"};
    std::cout<<"request class\n";
    char **t;
    t = ft_split(buf,'\n');// all six elements
    //method//host//user-Agent//accept_encoding//connection
    
    for(int j =0;j < 6;j++)
        table_index[j] = find_important_request(t,the_six_request[j],the_six_request[j].length());
    int i = 0;
    while(t[i])
        i++;
    request_line = t[table_index[0]];
    ////////////////
    host = t[table_index[1]];
    User_agent = t[table_index[2]];
    Accept_Language = t[table_index[3]];
    Accept_Encoding = t[table_index[4]];
    Connection = t[table_index[5]];
};

Request::~Request()
{
    
};

void Request::get_methode()
{
    //first line//
    char **three_var;
    three_var = ft_split(request_line.c_str(),' ');
    methode = three_var[0];//Get//Post//Delete//Connect
    Request_uri = three_var[1];//path//uri//etc..
    http_version = three_var[2];
    //need to free three_var ....
    /////host//////
    char **s = ft_split(host.c_str(),' ');
    host = s[1];
    //////need to free s //////
}

void Request::get_header()
{
    
}
