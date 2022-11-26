/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:53:30 by mfagri            #+#    #+#             */
/*   Updated: 2022/11/26 19:07:07 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"


    // (none): If no modifiers are present, the location is interpreted as a prefix match. This means that the location given will be matched against the beginning of the request URI to determine a match.
    // =: If an equal sign is used, this block will be considered a match if the request URI exactly matches the location given.
    // ~: If a tilde modifier is present, this location will be interpreted as a case-sensitive regular expression match.
    // ~*: If a tilde and asterisk modifier is used, the location block will be interpreted as a case-insensitive regular expression match.
    // ^~: If a carat and tilde modifier is present, and if this block is selected as the best non-regular expression match, regular expression matching will not take place.

Response::Response()
{
    uri = "";
    status = 0;
    res = "";
}

Response::Response(Request &req)
{
    uri = req.get_uri();
    int pos;
    pos = 0;
    printf("{%s}\n",uri.c_str());
    if(uri.length() == 1)
        uri = "/index.html";
    std::string root = "/Users/mfagri/Desktop/Webserv/pages";/////root
    status = req.get_status_code();
    std::string method = "GET";
    std::string location_match= "/ok.html";///location
    char **optional_modifier = (char **)malloc(sizeof(char *)*5);
    optional_modifier[0] ="=";
    optional_modifier[1] ="^~";
    optional_modifier[2] ="*~";
    optional_modifier[3] ="~";
    optional_modifier[4] = NULL;
    // if(find_option(optional_modifier,"=") != 404 && location_match == uri && pos == 0)
    // {
            root+=uri;
            if(req.get_methode() == method)
            {
                std::cout<<"creat response\n";
                ft_creat_file(root,0);
                pos = 1;
            }
            else
                ft_creat_file(root,1);
                
    // }
    // if(find_option(optional_modifier,"^~") != 404 && location_match == uri && pos == 0)
    // {
    //     //get the file
    // }
    // if(find_option(optional_modifier,"*~") != 404 && location_match == uri && pos == 0)
    // {
    //     //get the file
    // }  
    // if(find_option(optional_modifier,"~") != 404 && location_match == uri && pos == 0)
    // {
    //     //get the file
    // }
}

int find_option(char **s,std::string op)
{
    int i;
    i = 0;
    while(s[i])
    {
        if(strcmp(s[i],op.c_str()) == 0)
            return (i);
        i++;
    }
    return (404);
}

void Response::ft_creat_file(std::string root,int ok)
{
    char buf[3000];
    int i = open(root.c_str(),O_RDWR,777);
    std::string str;
    char ss[3000] = {0};
    if(i != -1 && ok == 0)
    {
        ///puts("ffffff");
        read(i,ss,3000);
        //puts(ss);
        str = ss;
        memset(buf,0,3000);
        strcpy(buf,"HTTP/1.1 ");
        strcat(buf,ft_itoa(status));
        strcat(buf," OK\nDate: Thu, 24 Nov 2022 14:37:49 GMT\nContent-Type: text/html\nContent-Length: "); //9\n\n"
        int lenght;
        lenght = str.length();
        //std::cout<<"lenght:"<<lenght<<std::endl;
        std::string v = ft_itoa(lenght);
        std::string final = v+"\n\n"+str;
        ft_strlcat(buf,final.c_str(),3000);
    }
    else
    {
        //std::ifstream f("/Users/mfagri/Desktop/Webserv/pages/not_found.html");
        int i = open("/Users/mfagri/Desktop/Webserv/pages/not_found.html",O_RDWR,777);
        read(i,ss,3000);
        str = ss;
        memset(buf,0,3000);
        strcpy(buf,"HTTP/1.1 ");
        strcat(buf,ft_itoa(404));
        strcat(buf," OK\nDate: Thu, 24 Nov 2022 14:37:49 GMT\nContent-Type: text/html\nContent-Length: "); //9\n\n"
        int lenght;
        lenght = str.length();
        strcat(buf,ft_itoa(lenght));
        //std::cout<<"lenght:"<<lenght<<std::endl;
        //std::string v = ft_itoa(lenght);
        strcat(buf,"\n\n");
        strcat(buf,ss);
        //std::string final = v+"\n\n"+str;
        // ft_strlcat(buf,final.c_str(),3000);
    }
    res = buf;
    //puts(res);
}

char * Response::get_res()
{
    return res;
}