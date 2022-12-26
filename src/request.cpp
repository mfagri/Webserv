/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:06:24 by mfagri            #+#    #+#             */
/*   Updated: 2022/12/26 18:19:46 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_info.hpp"

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

Request::Request(std::string buf)
{
    max_body = 5000000;
    status_code = 200;
    chunked = 0;
    if(buf[0] == '\0')
    {
        return;
    }
    int in = 0;
    int i = 0;

    while(i < (int)strlen(buf.c_str()) - 2)
    {
        if(buf[i] == '\r' && buf[i + 1] == '\n' && buf[i+2] == '\r' && buf[i + 3] == '\n')
        {
                in = 1;
            break;
        }
        i++;
    }
    int leng;

	leng = buf.find("\n");
    request_line = buf.substr(0,leng-1);
    request_header = buf.substr(0, buf.find("\r\n\r\n"));
    if(in)
    {
       Body = buf.substr(buf.find("\r\n\r\n"));
    }
    parse_request_line(request_line);
    if(parse_headers(request_header))
    {
        puts("header");
        return;
    }
    if(in)
    {
        if(Body.size() < 5)
            return;
        if(chunked)
        {
            ft_chunked();
        }
        Bodypost = Body;
        ft_parse_body();
    }
    return;
}

Request::~Request()
{
    headers.clear();
}

int Request::ft_check_request()
{
    if(headers["Content-Type"].empty() && methode == "POST")
    {
        std::cout<<"Missing Content-Type"<<std::endl;
        status_code = 400;
        return (1);
    }
    if(atol(headers["Content-Length"].c_str()) > max_body)
    {
        std::cout<<" max Content-Lenght size has been reached ! "<<std::endl;
        status_code = 431;
        return (1);
    }
    if(headers["Host"].empty())
    {
        status_code = 400;
        return (1);
    }
    if(headers["Connection"].empty())
    {
        status_code = 400;
        return (1);
    }
    if( headers["Transfer-Encoding"] == "chunked")
    {
        chunked = 16;
        status_code = 200;
    }
    else
    {
        if(atoi(headers["Content-Length"].c_str()) <= 0 && methode == "POST")
        {
            status_code = 411;
            return (1);
        }
    }
    return (0);
}
int Request::parse_request_line(std::string req)
{
    int status = 0;
    int i = 0;
    std::string Http;
    
    methode = strtok((char *)req.c_str()," ");
    
    if(methode != "GET" && methode != "POST" && methode != "DELETE")
    {
        std::cout<<"501 Not Implemented"<<std::endl;
        status_code = 501;
        return (1);
    }
    Request_uri = strtok(NULL," ");
    if(Request_uri.at(0) != '/')
    {
        std::cout<<"BAD request"<<std::endl;
        status_code = 400;
        return (1);
    }
    
    Http = strtok(NULL," ");
    if(Http != "HTTP/1.1")
    {
        std::cout<<"505 HTTP Version Not Supported"<<std::endl;
        status_code = 505;
        return (1);
    }
    
    if(strchr(Request_uri.c_str(),'?'))
    {
        i = 0;
        strtok((char *)Request_uri.c_str(),"?");
        char *s_query = strtok(NULL, "?");
        if (s_query) {
            
            char **t = ft_split(s_query,'&');
            while(t[i])
            {
                queryuri += t[i];
                queryuri += "&";
                char* key = strtok(t[i],"=");
                char* value = strtok(NULL,"\0");
                if (value && key)
                {
                    query.insert(std::pair<std::string, std::string>(key, value));
                }
                i++;
            }
            ft_free2(t);
        }
    }

    return (status);
}
int Request::parse_headers(std::string headres_)
{
    size_t i;
    size_t j;
    size_t tmp;
    j = 0;
    int status = 0;
    std::string tohelp;
    std::vector<std::string> hedss;
    j = 0;
    while (j < headres_.length())
	{
			j = headres_.find("\r\n")+2;
			if (j > headres_.length())
				break ;
            tmp = headres_.substr(j).find("\r\n");
            if (tmp == std::string::npos)
            {
                hedss.push_back(headres_.substr(j, headres_.length() - 1));
                break ;
            }
            hedss.push_back(headres_.substr(j, tmp));
			headres_ = headres_.substr(j);
	}
    i = 0;
    while(i < hedss.size())
    {
        std::string key = hedss[i].substr(0 ,hedss[i].find(":"));
        std::string value = hedss[i].substr(hedss[i].find(":")+1);
        value = value.substr(value.find(" ")+1);
        if(!key.empty() && !value.empty())
        {
            headers.insert(std::pair<std::string, std::string>(key, value));
        }
        key.clear();
        value.clear();
        i++;
    }
    if (status_code == 200)
        status = ft_check_request();
    hedss.clear();
    tohelp.clear();
    headres_.clear();
    return (status);
}
int Request::get_status_code()
{
    return (status_code);
}
std::string Request::get_queryuri()
{
    return (queryuri);
}
int Request::ft_chunked(void)
{
    std::string sbody;
    int k = 0;
    size_t i = 0;
    i = 0;
    k = 0;
    while(i < Body.size())
    {
        std::string integr;
        if((Body[i] =='\r' && Body[i+1] == '\n'))
        {
            i+=2;
        }
        if(isdigit(Body[i]) || isalpha(Body[i]))
        {
            while (Body[i] !='\r' && Body[i+1] != '\n')
            {
                integr += Body[i];
                i++;
            }
            k = (int)strtol(integr.c_str(), NULL, 16);
        }
        if((Body[i] =='\r' && Body[i+1] == '\n'))
        {
            i+=2;
        }
        while (k)
        {
            sbody += Body[i];
            k--;
            i++;
        }
    }
    Body.clear();
    Body = sbody;
    sbody.clear();
    return (0);
}

int Request::ft_parse_body()
{
    if(strncmp(headers["Content-Type"].c_str(),"multipart/form-data; boundary",strlen("multipart/form-data; boundary")) == 0)
    {
        std::vector<std::string> boundraies;
        std::string b;
        std::string test;
        std::string names;
        std::string bounday = headers["Content-Type"].substr(headers["Content-Type"].find("boundary=") + 9, headers["Content-Type"].substr(headers["Content-Type"].find("boundary=") + 9).find("\r\n") - 1);
        b = "--";
        b += bounday;
        
        for (size_t i = 0, index = -1; true; i++) {
        index = Body.find(b, index + 1);
        boundraies.push_back(Body.substr(index + 0, Body.find(b, index + 1) - index));
        if (boundraies[i].find(b + "--") != Body.npos) {
            boundraies.pop_back();
            break ;
        }
    }
        size_t i ;
        i = -1;
        while (++i < boundraies.size())
		{
            if(boundraies[i] == "-\r\n")
            {
                std::cout<<boundraies[i]<<std::endl;
                boundraies.erase(boundraies.begin() + i);
            }
			else
            {
                if(boundraies[i].find("filename=") != std::string::npos)
                {
                    std::string filename = boundraies[i].substr(boundraies[i].find("filename=") + 10, boundraies[i].substr(boundraies[i].find("filename=") + 10).find("\r\n") - 1);
                    std::ofstream file( "../links/upload/" + filename);
                    std::string content = boundraies[i].substr(boundraies[i].find("Content-Type:"));
                    std::string content2 = content.substr(content.find("\r\n\r\n") + 4);
                    file << content2;
                    file.close();
                }
                else
                {
                    std::string body3;
                    std::string name = boundraies[i].substr(boundraies[i].find("name=") + 6, boundraies[i].substr(boundraies[i].find("name=") + 6).find("\r\n") - 1);
                    body3 = boundraies[i].substr(boundraies[i].find("\r\n")+2);
                    body3 = body3.substr(body3.find("\r\n")+2);
                    char *s = ft_strtrim(body3.c_str(),"\r\n");
                    body3 = s;
                    free(s);
                    body_query.insert(std::pair<std::string,std::string>(names,body3));
                }
            }
		}
    }     
    else if(headers["Content-Type"] == "application/x-www-form-urlencoded")
    {
        std::string key = strtok((char *)Body.c_str(),"=");
        std::string value =strtok(NULL,"\0");
        if(!key.empty() && !value.empty())
            body_query.insert(std::pair<std::string,std::string>(key,value));
    }
    else
    {
        if(Body.empty())
            return (0);
        if((Body[0] == '\r' || Body[0] == '\n' ) && !chunked )
        {
            if(Body.size() < 5)
                return(0);
            size_t pos = Body.find('\n') + 3;
            Body=Body.substr(pos);
        }
        std::ofstream file("../links/upload/" + headers["Content-Type"].replace(headers["Content-Type"].find('/'), 1, "."));
        file << Body;
        file.close();
    }
    return (0);
}

std::string Request::get_uri()
{
    return (Request_uri);
}
std::string Request::get_methode()
{
    return (methode);
}
std::string Request::get_body_req()
{
    return (Bodypost);
}
std::map<std::string,std::string> Request::get_headers()
{
    return (headers);
}