/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:06:24 by mfagri            #+#    #+#             */
/*   Updated: 2022/11/20 22:49:56 by mfagri           ###   ########.fr       */
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
    
}

Request::Request(char *buf)
{
    //request_line
    //header_fields
    //body
    chunked = 0;
    std::cout<<buf<<std::endl;
    int in = 0;
    int i = 0;
    while(i < (int)strlen(buf) - 2)
    {
        if(buf[i] == '\r' && buf[i + 1] == '\n' && buf[i+2] == '\r' && buf[i + 3] == '\n')
        {
            buf[i + 3] = '|';
            // std::cout<<buf[i + 3]<<std::endl;
            std::cout<<buf[i + 4]<<std::endl;
            std::cout<<buf[i + 5]<<std::endl;
            std::cout<<buf[i + 6]<<std::endl;
            if(buf[i + 4])
                in = 1;
            // std::cout<<"dfgdfgdfdfgfgf\n";
        }
        i++;
    }
    //request Line
    // std::cout<<in<<std::endl;
    request_line = strtok(buf,"\n");
    request_header = strtok(NULL,"|");
    //////if body in request //////////////
    if(in)
        Body = strtok(NULL,"\0");
    std::cout<<"Body"<<Body<<"end\n";
    ////////////////////////////////////////
    methode = strtok((char *)request_line.c_str()," ");
    // std::cout<<"methode : "<<methode<<std::endl;
    Request_uri = strtok(NULL," ");
   
    // check query string 
    // std::cout<<"uri : "<<Request_uri<<std::endl;
    char * s= strtok(NULL," ");
    s = strtok(s,"/");
    http_version = strtok(NULL,"/");
    http_version = ft_strtrim(http_version.c_str(),"\r");
    //printf("{%s}\n",http_version.c_str());
    // std::cout<<"http version : "<<http_version<<std::endl;
    if(strchr(Request_uri.c_str(),'?'))
    {
        i = 0;
        char *s_query = ft_strtrim(Request_uri.c_str(),"/?");
        char **t = ft_split(s_query,'&');
        while(t[i])
        {
            puts("here");
            char *key = strtok(t[i],"=");
            char *value = strtok(NULL,"\0");
            query.insert(std::pair<std::string, std::string>(key, value));
            i++;
            
        }
    }
    //////////////////////////////////////////////////////////////
    i = 0;
    char **ss = ft_split(request_header.c_str(),'\n');
    int j = 0;
    while(ss[j])
    {
        ss[j]= ft_strtrim(ss[j],"\r");
        j++;
    }
    //printf("j = %d\n",j);
    //printf("ss 9= %s\n",ss[8]);
    // if(strcmp(ss[8],"") == 0)
    //      printf("ss 9= %s\n",ss[8]);
    //puts(request_header.c_str());
    while(i < j - 1)
    {
        // puts("hna2");
        char *key = strtok(ss[i],":");
        char *value = strtok(NULL,"\0");
        headers.insert(std::pair<std::string, std::string>(key, ft_strtrim(value," ")));
        i++;
    }
    ft_free2(ss);
    std::cout<<methode<<std::endl;
    std::cout<<Request_uri<<std::endl;
    
    std::map<std::string, std::string>::iterator itr;
    for (itr = headers.begin(); itr != headers.end(); ++itr) {
        std::cout << '\t' <<"{"<<itr->first <<"}"<< '\t' <<"{"<<itr->second
             <<"}"<< '\n';
    }
     std::map<std::string, std::string>::iterator it;
    for (it = query.begin(); it != query.end(); ++it) {
        std::cout << '\t' <<"{"<<it->first <<"}"<< '\t' <<"{"<<it->second
             <<"}"<< '\n';
    }
    printf("{%s}\n",Body.c_str());
    ft_check_request();
}

Request::~Request()
{
    headers.clear();
}

int Request::ft_check_request()
{
    status_code = 200;
    // std::cout<<http_version<<std::endl;
    if(Request_uri.at(0) != '/')
    {
        std::cout<<"BAD request"<<std::endl;
        status_code = 400;
    }
    if(http_version[0] != '1' && http_version[1] != '.' && http_version[2] != '1')
    {
        std::cout<<"505 HTTP Version Not Supported"<<std::endl;
        status_code = 505;
        return (1);
    }
    if(headers["Content-Type"].c_str() == NULL)
    {
        std::cout<<"Missing Content-Type"<<std::endl;
        status_code = 400;
    }
    //////////////////////////////
    // 503 Service Unavailable////
    /////check size of packge/////
    /////////////////////////////
    if(methode != "GET" && methode != "POST" && methode != "DELETE")
    {
        std::cout<<"501 Not Implemented"<<std::endl;
        status_code = 501;
        return (1);
    }
    if(methode == "POST")
    {
        // if(atoi(headers["Content-Length"].c_str()) <= 0 )
        // {
        //     status_code = 411;
        //     return (1);
        // }
        // printf("eco : %d\n",atoi(headers["Content-Length"].c_str()));
        // printf("TE: {%s} \n",headers["Transfer-Encoding"].c_str());
        if( headers["Transfer-Encoding"] == "" && atoi(headers["Content-Length"].c_str()) <= 0 )
        {
            status_code = 411;
            return (1);
        }
        if( headers["Transfer-Encoding"] == "chunked")
        {
            chunked = 16;
            status_code = 200;
        }
    }
    return (0);
}

int Request::get_status_code()
{
    return (status_code);
}