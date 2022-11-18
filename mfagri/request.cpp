/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:06:24 by mfagri            #+#    #+#             */
/*   Updated: 2022/11/18 21:03:39 by mfagri           ###   ########.fr       */
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
    //request_line
    //header_fields
    //body
    int in = 0;
    int i = 0;
    while(i < (int)strlen(buf) - 2)
    {
        if(buf[i] == '\n' && buf[i + 1] == '\n')
        {
            buf[i + 1] = '|';
            in = 1;
        }
        i++;
    }
    //request Line
    request_line = strtok(buf,"\n");
    request_header = strtok(NULL,"|");
    //////if body in request //////////////
    if(in)
        Body = strtok(NULL,"|");
    ////////////////////////////////////////
    methode = strtok((char *)request_line.c_str()," ");
    // std::cout<<"methode : "<<methode<<std::endl;
    Request_uri = strtok(NULL," ");
    // std::cout<<"uri : "<<Request_uri<<std::endl;
    char * s= strtok(NULL," ");
    s = strtok(s,"/");
    http_version = atof(strtok(NULL,"/"));
    // std::cout<<"http version : "<<http_version<<std::endl;

    //////////////////////////////////////////////////////////////
    i = 0;
    char **ss = ft_split(request_header.c_str(),'\n');
    //puts(request_header.c_str());
    while(ss[i])
    {
        //puts("hna2");
        char *key = strtok(ss[i],":");
        char *vallue = strtok(NULL,"\0"); 
        headers.insert(std::pair<std::string, std::string>(key, vallue));
        i++;
        if(ss[i+1] == NULL)
            break;
    }
    ft_free2(ss);
    ft_check_request();
};

Request::~Request()
{
    headers.clear();
};

int Request::ft_check_request()
{
    if(http_version != 1.1)
    {
        status_code = 400;
        return (1);
    }
    if(methode != "GET" && methode != "POST" && methode != "DELETE")
    {
        status_code = 400;
        return (1);
    }
    if(methode == "POST")
    {
        if(atoi(headers["Content-Length"].c_str()) < 1)
        {
            status_code = 400;
            return (1);
        }
    }
    return (0);
}

