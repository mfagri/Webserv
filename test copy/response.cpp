/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:53:30 by mfagri            #+#    #+#             */
/*   Updated: 2022/12/03 20:57:09 by mfagri           ###   ########.fr       */
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
    // uri = "";
    // status = 0;
    // res = "";
    
}

Response::~Response()
{
    bzero(res,strlen(res)); 
}
Response::Response(Request &req)
{
    uri = req.get_uri();
    reqheaders = req.get_headers();
    std::string errors[6] = {"404","400","501","505","411","431"};
    std::string msgs[6] = {"404 Not found",
                           "400 Bad Request",
                           "501 Not Implemented",
                           "505 HTTP Version Not Supported",
                           "411 Length Required",
                           "431 Request Header Fields Too Large"};
    
    int i = 0;
    while(i < 6)
    {
        errormsg.insert(std::pair<int,std::string>(atoi(errors[i].c_str()),msgs[i]));
        i++;
    }
    // std::map<int, std::string>::iterator it;
    // for (it = errormsg.begin(); it != errormsg.end(); ++it) {
    //     std::cout << '\t' <<"{"<<it->first <<"}"<< '\t' <<"{"<<it->second
    //          <<"}"<< '\n';
    // }
    // int pos;
    // pos = 0;
    // printf("{%s}\n",uri.c_str());
    if(uri.length() == 1)
        uri = "/index.html";
    std::string root = "../links/pages";/////root
    status = req.get_status_code();
    // std::string method[3] = {"GET","POST","DELETE"};
    // std::string location_match= "/ok.html";///location
    // char **optional_modifier = (char **)malloc(sizeof(char *)*5);
    // optional_modifier[0] ="=";
    // optional_modifier[1] ="^~";
    // optional_modifier[2] ="*~";
    // optional_modifier[3] ="~";
    // optional_modifier[4] = NULL;
    // if(find_option(optional_modifier,"=") != 404 && location_match == uri && pos == 0)
    // {
            root+=uri;
            if(!allow_methode(req.get_methode()) && status == 200)
            {
                std::cout<<"creat response\n";
                ft_creat_file(root,0);
                // pos = 1;
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
int Response::allow_methode(std::string m)
{
    std::string methodes[3] ={"GET","POST","DELETE"};
    int i = 0;
    while(i < 3)
    {
        if(m == methodes[i])
            return (0);
        i++;
    }
    return(1);
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
    //char *infile;
    int i = open(root.c_str(),O_RDWR,777);
    std::string str;
    char ss[3000] = {0};
    if(i != -1 && ok == 0)
    {
        // infile = strdup("<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n  <meta charset=\"UTF-8\">\n  <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n  <title>Document</title>\
        // \n</head>\n<body>\n  <h1> Hiiiiii  </h1>\n</body>\n</html>\n");
        // write(i,infile,strlen(infile));
        // ///puts("ffffff");
        read(i,ss,3000);
        // //puts(ss);
        // // free(infile);
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
        if(status == 200)
            status = 404;
        //std::ifstream f("/Users/mfagri/Desktop/Webserv/pages/not_found.html");
        // int i = open("/Users/mfagri/Desktop/Webserv/pages/not_found.html",O_RDWR,777);
        // read(i,ss,3000);
        str = ft_generat_html();
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
        strcat(buf,(const char *)str.c_str());
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

char *Response::ft_generat_html()
{
    char *infile;
    infile = strdup("<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n  <meta charset=\"UTF-8\">\n  <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n  <title>Document</title>\
        \n</head>\n<body>\n  <h1> ");
        //Hiiiiii  </h1>\n</body>\n</html>\n");
    //puts(errormsg[404].c_str());
    char *msg = strdup(errormsg[status].c_str());
    char *endhtml = strdup("  </h1>\n</body>\n</html>\n");
    infile = ft_strjoin(infile,msg);
    infile = ft_strjoin(infile,endhtml);
    //puts(infile);
    free(msg);
    free(endhtml);
    return (infile);
}