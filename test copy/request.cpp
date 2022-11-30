/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:06:24 by mfagri            #+#    #+#             */
/*   Updated: 2022/12/01 00:30:16 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_info.hpp"

//414 URI Too Long
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

Request::Request(std::string buf)
{
   //std::cout<<buf<<std::endl;
    //exit(1);
    //request_line
    //header_fields
    //body
    // char *buf = strdup((const char *)b.c_str());
    max_body = 5000000;
    // max_body = 1024;
    status_code = 200;
    chunked = 0;
    if(buf[0] == '\0')
    {
        puts("fefe");
        return;
    }
    int in = 0;
    int i = 0;

    while(i < (int)strlen(buf.c_str()) - 2)
    {
        if(buf[i] == '\r' && buf[i + 1] == '\n' && buf[i+2] == '\r' && buf[i + 3] == '\n')
        {
            if(buf[i + 4])
                in = 1;
            break;
        }
        i++;
    }
    int leng;

	leng = buf.find("\n");
    request_line = buf.substr(0,leng-1);
    request_header = buf.substr(0, buf.find("\r\n\r\n"));
    // std::cout<<request_header<<std::endl;
    // puts("**************************");
    //////if body in request //////////////
    if(in)
       Body = buf.substr(buf.find("\r\n\r\n"));
    if(parse_request_line(request_line))
    {
        printf("in line\n");
        exit(1);
    }
    if(parse_headers(request_header))
    {
        printf("%d\n",status_code);
        printf("in headres\n");
        return;
    }
    if(in)
    {
        if(chunked)
        {
            puts("fdsfdffdsfdfdfdsfdsfdsfdsfdsfdsfadafdf");
            ft_chunked();
        }
        ft_parse_body();
    }
    ////////////////////////////////////////
    //////////////////////////////////////////////////////////////
    // std::cout<<"{"<<methode<<"}"<<std::endl;
    // std::cout<<"{"<<Request_uri<<"}"<<std::endl;
    
//     std::map<std::string, std::string>::iterator itr;
//     for (itr = headers.begin(); itr != headers.end(); ++itr) {
//         std::cout << '\t' <<"{"<<itr->first <<"}"<< '\t' <<"{"<<itr->second
//              <<"}"<< '\n';
//     }
//      std::map<std::string, std::string>::iterator it;
//     for (it = body_query.begin(); it != body_query.end(); ++it) {
//         std::cout << '\t' <<"{"<<it->first <<"}"<< '\t' <<"{"<<it->second
//              <<"}"<< '\n';
//     }
//     printf("{%s}\n",methode.c_str());
//     printf("{%s}\n",headers["Content-Type"].c_str());
//     printf("{%s}\n",headers["Content-Length"].c_str());
//     printf("{%s}\n",headers["Transfer-Encoding"].c_str());
//    // printf("{%s}\n",headers[].c_str());
    //ft_check_request();
}

Request::~Request()
{
    headers.clear();
}

int Request::ft_check_request()
{
    if(headers["Content-Type"].c_str() == NULL)
    {
        std::cout<<"Missing Content-Type"<<std::endl;
        status_code = 400;
        return (1);
    }
    if(atol(headers["Content-Length"].c_str()) > max_body)
    {
        std::cout<<" max Content-Lenght size has been reached ! "<<std::endl;
        status_code = 400;
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
    //////////////////////////////
    // 503 Service Unavailable////
    /////check size of packge/////
    /////////////////////////////
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
    // printf("=> %s\n",methode.c_str());
    // exit(1);
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
    //////////////////////////////////
    //if(open(path+uri) = -1)
    //{
    //  error  
    //}
    //////////////////////////////////
    char * s = strtok(NULL," ");
    s = strtok(s,"/");
    Http = s;
    if(Http != "HTTP")
    {
        
        std::cout<<"Not Supported"<<std::endl;
        status_code = 400;
        return (1);
    }
    http_version = strtok(NULL,"/");
    http_version = ft_strtrim(http_version.c_str(),"\r");
    if(http_version[0] != '1' && http_version[1] != '.' && http_version[2] != '1')
    {
        std::cout<<"505 HTTP Version Not Supported"<<std::endl;
        status_code = 505;
        return (1);
    }
    // check query string 
    if(strchr(Request_uri.c_str(),'?'))
    {
        i = 0;
        char *s_query = ft_strtrim(Request_uri.c_str(),"/?");
        char **t = ft_split(s_query,'&');
        while(t[i])
        {
            char *key = strtok(t[i],"=");
            char *value = strtok(NULL,"\0");
            query.insert(std::pair<std::string, std::string>(key, value));
            i++;
        }
        ft_free2(t);
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
    std::cout<<headres_  << std::endl << std::endl;
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
    // hedss.push_back(headres_.substr(0,headres_.find("\r\n")));
    // std::cout<<headres_<<std::endl;
    // puts("sdsd");
    i = 0;
    while(i < hedss.size())
    {
        char *key = strtok((char *)hedss[i].c_str(),":");
        char *value = strtok(NULL,"\0");
        if(key && value)
        {
            headers.insert(std::pair<std::string, std::string>(key, ft_strtrim(value," ")));
        }
        i++;
    }
    
    i = 0;
    while(i < hedss.size())
    {
        std::cout<<"h1{"<<hedss[i]<<"}"<<std::endl;
        i++;
    }
    // exit (0);
    status = ft_check_request();
    return (status);
}
int Request::get_status_code()
{
    return (status_code);
}

int Request::ft_chunked(void)
{
    std::string sbody;
    int k = 0;
    int i = 0;
    i = 0;
    k = 0;
    while(Body[i])
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
// int datanumber(char **bodyendl)
// {
//     int d=0;
//     int i = 0;
//     while(bodyendl[i])
//     {
//         if(bodyendl[i][0] != '\0')
//         {
//             if(strchr(bodyendl[i],'=')&&strnstr(bodyendl[i],"form-data",strlen(bodyendl[i])))
//             {
//                 d++;
//             }
//         }
//         i++;
//     }
//     return (d);
// }
int Request::ft_parse_body()
{
    //puts("hnaaa");//for binary
    if(strncmp(headers["Content-Type"].c_str(),"multipart/form-data; boundary",strlen("multipart/form-data; boundary")) == 0)
    {
        std::vector<std::string> boundraies;
        std::string b;
        std::string test;
        std::string names;
        std::string bounday = headers["Content-Type"].substr(headers["Content-Type"].find("boundary=") + 9, headers["Content-Type"].substr(headers["Content-Type"].find("boundary=") + 9).find("\r\n") - 1);
        b = "--";
        b += bounday;
        
        Body = Body.substr(Body.find(b));
		unsigned long j = 0;
		while (j < Body.length())
		{
			j = Body.find(b) + b.length() + 1;
			if (j > Body.length())
				break ;
            boundraies.push_back(Body.substr(j, Body.substr(j).find(b)));
			Body = Body.substr(j);
		}
        
        size_t i ;
        i = -1;
        while (++i < boundraies.size())
		{
            if(boundraies[i] == "-\r\n")
            {
                boundraies.erase(boundraies.begin() + i);
            }
			else
            {
                if(ft_strnstr(boundraies[i].c_str(),"filename=",strlen(boundraies[i].c_str())))
                {
                    std::string filename = boundraies[i].substr(boundraies[i].find("filename=") + 10, boundraies[i].substr(boundraies[i].find("filename=") + 10).find("\r\n") - 1);
                    std::ofstream file( "./files/" + filename);
                    std::string content = boundraies[i].substr(boundraies[i].find("Content-Type:"));
                    std::string content2 = content.substr(content.find("\r\n\r\n") + 4);
                    file << content2;
                    file.close();
                }
                else
                {
                    std::string body3;
                    names = boundraies[i].substr(0,boundraies[i].find("\r\n"));
                    body3 = boundraies[i].substr(boundraies[i].find("\r\n"));
                    body3 = ft_strtrim(body3.c_str(),"\r\n");
                    names = ft_strtrim(strrchr(names.c_str(),'='),"\"=");
                    body_query.insert(std::pair<std::string,std::string>(names,body3));
                }
            }
		}
    }     
    else if(headers["Content-Type"] == "application/x-www-form-urlencoded")
    {
        char *key = strtok((char *)Body.c_str(),"=");
        char *value =strtok(NULL,"\0");
        body_query.insert(std::pair<std::string,std::string>(key,value));
    }
    else
    {
        //std::cout<<Body<<std::endl;//auther type
        if(headers["Content-Type"] == "image/png")
        {
            std::ofstream file( "./files/binary.png");
            file << Body;
            file.close();
        }
        else if(headers["Content-Type"] == "application/pdf")
        {
            std::ofstream file( "./files/binary.pdf");
            file << Body;
            file.close();
        }
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

std::map<std::string,std::string> Request::get_headers()
{
    return (headers);
}