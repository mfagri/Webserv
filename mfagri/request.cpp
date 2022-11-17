/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:06:24 by mfagri            #+#    #+#             */
/*   Updated: 2022/11/17 23:43:06 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request.hpp"
#include <string>
#include <string.h>
/// methods// post | get | delete | connect | put
char *ft_delet_char(char *s,char c)
{
	int i = 0;
	while(s[i])
	{
		if(s[i] == c)
			s[i] = ' ';
		i++;
	}
	return (s);
}
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
    //std::cout<<"request class\n";
    // std::cout<<"*****************************\n";
    // std::cout<<buf;
    // std::cout<<"*****************************\n";
    int table_index[10];
    std::string the_six_request[10] = {"GET","Host:","User-Agent:","Accept-Language:",\
    "Accept-Encoding:","Connection:","Accept:","Transfer-Encoding","Content-Type","Content-Length"};
    char **t;
    t = ft_split(buf,'\n');// all six elements
    //method//host//user-Agent//accept_encoding//connection
    for(int j =0;j < 10;j++)
        table_index[j] = find_important_request(t,the_six_request[j],the_six_request[j].length());
    ////////////////////////////////////////////////////////
    request_line = t[0];
    host = t[table_index[1]];
	if(table_index[2]!= 404)
    	User_agent = t[table_index[2]];
	else
		User_agent = "not found";
	if(table_index[2]!= 404)
    	Accept_Language = t[table_index[3]];
	else
		Accept_Language = "not found";
	if(table_index[4]!= 404)
    	Accept_Encoding = t[table_index[4]];
	else
		Accept_Encoding = "not found";
	if(table_index[5]!= 404)
    	Connection = t[table_index[5]];
	else
		Connection = "not found";
	if(table_index[6]!= 404)
    	Accept = t[table_index[6]];
	else
		Accept = "not found";
	if(table_index[7]!= 404)
		Transfer_Encoding = t[table_index[7]];
	else
		Transfer_Encoding = "not found";
	if(table_index[8]!= 404)
		Content_Type = t[table_index[8]];
	else
		Content_Type = "not found";
	if(table_index[9]!= 404)
		Content_Length = t[table_index[9]];
	else
		Content_Length = "not found";
    ///////////////////////////////////////////////////
	ft_free2(t);
    get_methode();
    get_header();
    print_request();
    ft_check_request();
};

Request::~Request()
{
    
};

void Request::get_methode()
{
    //first line//
    char **three_var;
    three_var = ft_split(request_line.c_str(),' ');
    methode = ft_delet_char(three_var[0],'\r');//Get//Post//Delete//Connect
    Request_uri = ft_delet_char(three_var[1],'\r');;//path//uri//etc..
    http_version = ft_delet_char(three_var[2],'\r');;
    //need to free three_var ....
    ft_free2(three_var);
    /////host//////
    char **s = ft_split(host.c_str(),' ');
    host = s[1];
    ft_free2(s);
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
    s = ft_split(Accept_Language.c_str(),',');
    Accept_Language = s[0];
    ft_free2(s);
    int j = 0;
    while(Accept_Language[j])
    {
        if(Accept_Language[j] == ',')
            Accept_Language[j] = 0;
        j++;
    }
    ////////Accept-Encoding///////////////2
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
    Accept_Encoding.clear();
    while(s[i])
    {
        types[i] = s[i];
        //std::cout<<types[i];
        if(i != 0)
        {
            //std::cout<<i<<"\n";
            Accept_Encoding += types[i] + " ";
        }
        i++;
    }   
    ft_free2(s);
    /////////////Connection:////////////////////////
    s = ft_split(Connection.c_str(),' ');
    Connection = s[1];
    ft_free2(s);
    /////////////Accept:////////////////////////////
    s = ft_split(Accept.c_str(),' ');
    Accept = s[1];
    ft_free2(s);
    /////////////////////////////////////////////////
    // s = ft_split()
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
    std::cout<<"Connection: "<<Connection<<"\n";
    std::cout<<"accept: "<<Accept<<"\n";
    std::cout<<"accept_encoding :";
	puts(Accept_Encoding.c_str());
    std::cout<<"Transfer_encoding : "<<Transfer_Encoding<<"\n";
    std::cout<<"Content_type: "<<Content_Type<<"\n";
    std::cout<<"Content_Length: "<<Content_Length<<"\n";
    std::cout<<"//////////////////////////////////////\n";
}
int ft_check_http_version(std::string v)
{
    // std::cout<<"\""<<v<<"\"";
    size_t found = v.find('/');
    if (found != std::string::npos)
        if(v[found+1] != '1' || v[found +3] != '1' || v[found + 4] != ' ')
            return (1);
    // std::cout<<v[found+1]<<" "<<v[found +3]<<std::endl;
    return (0);
}
int Request::ft_check_request()
{
    /////http version///////
    if(ft_check_http_version(this->http_version))
    {
        std::cout<<"error in htt version\n";
        return (1);
    }
    return (0);
}