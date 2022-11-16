/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:06:24 by mfagri            #+#    #+#             */
/*   Updated: 2022/11/17 00:56:44 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request.hpp"
#include <string>
#include <string.h>
/// methods// post | get | delete | connect | put
void ft_free2(char **s)
{
    int i = 0;
    while(s[i])
        free(s[i++]);
    free(s);
}
int size_2(char **s)
{
    int i = 0;
    while(s[i])
        i++;
    return (i);    
}
int find_important_request(char **t,std::string s,int size)
{
    int i;
    i = 0;
    while(t[i])
    {
        if(strncmp(t[i],s.c_str(),size) == 0)
            return (i);
        i++;
    }
    return (404);
}
Request::Request()
{
    
};

Request::Request(char *buf)
{
    // std::cout<<"*****************************\n";
    // std::cout<<buf;
    // std::cout<<"*****************************\n";
    int table_index[7];
    //choise six element i my request 
    std::string the_six_request[7] = {"GET","Host:","User-Agent:","Accept-Language:","Accept-Encoding:","Connection:","Accept:"};
    std::cout<<"request class\n";
    char **t;
    t = ft_split(buf,'\n');// all six elements
    //method//host//user-Agent//accept_encoding//connection
    
    for(int j =0;j < 7;j++)
        table_index[j] = find_important_request(t,the_six_request[j],the_six_request[j].length());
    int i = 0;
    while(t[i])
        i++;
    request_line = t[table_index[0]];
    std::cout<<request_line<<"\n";
    ////////////////
    host = t[table_index[1]];
    User_agent = t[table_index[2]];
    Accept_Language = t[table_index[3]];
    Accept_Encoding = t[table_index[4]];
    Connection = t[table_index[5]];
    Accept = t[table_index[6]];
    get_methode();
    get_header();
    print_request();
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
    //////////User-Agent////////////////
    char **s = ft_split(User_agent.c_str(),' ');
    browser = s[1];
    ft_free2(s);
    //////////Accept-Languge///////////////
    s = ft_split(Accept_Language.c_str(),' ');
    Accept_Language = s[1];
    ft_free2(s);
    ////////Accept-Encoding///////////////
    int i =0 ;
    while(Accept_Encoding[i])
    {
        if(Accept_Encoding[i] == ',')
            Accept_Encoding[i]  = ' ';
        i++;
    }
    s = ft_split(Accept_Encoding.c_str(),' ');
    i = size_2(s);
    std::string types[i];
    i = 0;
    while(s[i])
    {
        Accept_Encoding = "";
        types[i] = s[i];
        std::cout<<types[i];
        if(i != 0)
        {
            
            std::cout<<i<<"\n";
            Accept_Encoding += types[i] + " ";
        }
        i++;
    }
    /////types strats from 1////    
    ft_free2(s);
    
    s = ft_split(Connection.c_str(),' ');
    Connection = s[1];
    ft_free2(s);
    s = ft_split(Accept.c_str(),' ');
    Accept = s[1];
    ft_free2(s);
}

void Request::print_request()
{
    std::cout<<"//////////////////////////////////////\n";
    std::cout<<"methode: "<<methode<<"\n";
    std::cout<<"http version: "<<http_version<<"\n";
    std::cout<<"request uri: "<<Request_uri<<"\n";
    std::cout<<"host: "<<host<<"\n";
    std::cout<<"browser: "<<browser<<"\n";
    std::cout<<"language: "<<Accept_Language<<"\n";
    std::cout<<"accept encoding: "<<Accept_Encoding<<"\n";
    std::cout<<"Connection: "<<Connection<<"\n";
    std::cout<<"accept: "<<Accept<<"\n";
    std::cout<<"//////////////////////////////////////\n";
}
