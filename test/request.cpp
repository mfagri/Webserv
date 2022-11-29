/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:06:24 by mfagri            #+#    #+#             */
/*   Updated: 2022/11/29 16:07:41 by mfagri           ###   ########.fr       */
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

Request::Request(std::string b)
{
   //printf("%s \n", b.c_str());
    //exit(1);
    //request_line
    //header_fields
    //body
    char *buf = strdup((const char *)b.c_str());
    max_body = 1000000;
    // max_body = 1024;
    status_code = 200;
    chunked = 0;
    if(buf[0] == '\0')
    {
        puts("fefe");
        return;
    }
    
    // std::cout<< b <<std::endl;
    puts("sdsd");
    int in = 0;
    int i = 0;
    while(i < (int)strlen(buf) - 2)
    {
        if(buf[i] == '\r' && buf[i + 1] == '\n' && buf[i+2] == '\r' && buf[i + 3] == '\n')
        {
            buf[i + 3] = '|';
            if(buf[i + 4])
                in = 1;
            break;
        }
        i++;
    }
    request_line = strtok(buf,"\n");
    request_header = strtok(NULL,"|");
    //////if body in request //////////////
    if(in)
        Body = strtok(NULL,"\0");

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
    //printf("{%s}\n",Body.c_str());
    //printf("{%s}\n",Body.c_str());
    //  exit(1);
    if(in)
    {
        if(chunked)
            ft_chunked();
        ft_parse_body();
    }
    ////////////////////////////////////////
    //////////////////////////////////////////////////////////////
    std::cout<<"{"<<methode<<"}"<<std::endl;
    std::cout<<"{"<<Request_uri<<"}"<<std::endl;
    
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
    int i;
    int j;
    int status = 0;

    char **ss = ft_split(headres_.c_str(),'\n');
    j = 0;
    while(ss[j])
    {
        ss[j]= ft_strtrim(ss[j],"\r");
        j++;
    }
    i = 0;
    while(i < j - 1)
    {
        char *key = strtok(ss[i],":");
        char *value = strtok(NULL,"\0");
        headers.insert(std::pair<std::string, std::string>(key, ft_strtrim(value," ")));
        i++;
    }
    ft_free2(ss);
    status = ft_check_request();
    return (status);
}
int Request::get_status_code()
{
    return (status_code);
}

int Request::ft_chunked(void)
{
    // char **s = ft_split(Body.c_str(),'\n');
    // std::vector<int> indexint;
    // std::vector<std::string> stringes;
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
            // printf("dd\n");
            i+=2;
        }
        if(isdigit(Body[i]) || isalpha(Body[i]))
        {
            while (Body[i] !='\r' && Body[i+1] != '\n')
            {
                // printf("here");
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
            // printf("{%c}\n",Body[i]);
            sbody += Body[i];
            k--;
            i++;
        }
    }
    Body.clear();
    Body = sbody;
    sbody.clear();
    //printf("my final body: {%s}\n",sbody.c_str());
    return (0);
}
// int findfile(std::string s)
// {
//     int i;
//     i = 0;
//     i = s.find("filename");
//     printf("{%d}\n",i);
//     if(i != -1)
//         return (1);
//     return (0);
// }
int datanumber(char **bodyendl)
{
    //int d=0;
    int i = 0;
    while(bodyendl[i])
    {
        // if(bodyendl[i][0] != '\0')
        // {
        //     if(strchr(bodyendl[i],'=')&&strnstr(bodyendl[i],"form-data",strlen(bodyendl[i])))
        //     {
        //         d++;
        //     }
        // }
        i++;
    }
    return (i);
}
int Request::ft_parse_body()
{
    if(strncmp(headers["Content-Type"].c_str(),"multipart/form-data; boundary",strlen("multipart/form-data; boundary")) == 0)
    {
        std::string body = Body;
        std::string b;
        std::string names;
        int i = 0;
        size_t index;
        char *bounday;
        bounday = (char *)strchr(headers["Content-Type"].c_str(),'=');
        bounday = bounday+1;
        b = "--";
        b += bounday;
    
        index = 0;
        while (index < body.length())
        {
            
            if(body.compare(index,strlen(b.c_str()),b) == 0)
            {
                body.erase(index,strlen(b.c_str()));
                body.insert(index,"\v");
            }
            index ++;
        }
        char **bodyendl = ft_split(body.c_str(),'\v');
        i = 0;
        int d = datanumber(bodyendl)-1;
        Data *data = new Data[d];
        while(bodyendl[i])
        {
            bodyendl[i] = ft_strtrim(bodyendl[i],"\r");
            i++;
        }
        i = 0;
        while(bodyendl[i])
        {
            if(bodyendl[i+1]==NULL)
                break;
            std::string body3;
            std::string test = strtok(bodyendl[i],"\r\n\r\n");
            body3 = strtok(NULL,"\0");
            body3 = ft_strtrim(body3.c_str(),"\r\n");
            if(ft_strnstr(test.c_str(),"filename",strlen(test.c_str())))
            {
                names = ft_strtrim(strrchr(test.c_str(),'='),"\"=");
                data[i].file = names;
                int pos = body3.find("\r\n\r\n");
                body3 = body3.substr(pos+strlen("\r\n\r\n"));
                data[i].datafile = body3;
                // puts("sds");
                // printf("%s\n",names.c_str());
                // std::ofstream file;
                // // file.open(names.c_str());
                std::string path = "./files/"+names;
                // file.open(path);
                // file<<body3;
                int fdf = open(path.c_str(),O_CREAT|O_RDWR,777);
                if(fdf < 0)
                {
                   puts("errrrrro"); 
                }
                write(fdf,body3.c_str(),body3.length());
                // std::ostringstream ss;
                // ss << file.rdbuf();
                // std::cout<<ss<<"\n";
            }
            else
            {
                names = ft_strtrim(strrchr(test.c_str(),'='),"\"=");
                body_query.insert(std::pair<std::string,std::string>(names,body3));
            }
            names.clear();
            body3.clear();
            i++;
        }
    }
    else if(headers["Content-Type"] == "application/x-www-form-urlencoded")
    {
        char *key = strtok((char *)Body.c_str(),"=");
        char *value =strtok(NULL,"\0");
        body_query.insert(std::pair<std::string,std::string>(key,value));
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