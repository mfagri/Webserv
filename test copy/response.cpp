/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:53:30 by mfagri            #+#    #+#             */
/*   Updated: 2022/12/09 21:04:56 by ntanjaou         ###   ########.fr       */
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
    //bzero(res.c_str(),strlen(res)); 
}
Response::Response(Request &req, std::vector<ServerData> servers)
{
    //puts("HERE1");
    reqheaders = req.get_headers();
    status = req.get_status_code();
    ServerData sv;
    int port = atoi(reqheaders["Host"].substr(reqheaders["Host"].find(":")+1).c_str());
    //std::cout<<"{"<<reqheaders["Host"].substr(reqheaders["Host"].find(":")+1)<<"}"<<std::endl;
    //std::cout<<port<<std::endl;
    size_t k = 0;
    while(k < servers.size())
    {
        if(port == servers[k].getPort())
        {
            sv = servers[k];
            break;
        }
        k++;
    }
    //puts("HERE2");
    // if(sv)
    std::string root = sv.getRoot();
    std::vector<std::map<std::string,std::string> > locations = sv.getLocations();
    //std::cout<< "here loc size : " << locations.size()<<std::endl;
    //exit(1);
    uri = req.get_uri();
    std::string errors[6] = {"404","400","501","505","411","431"};
    std::string msgs[6] = {"404 Not found",
                           "400 Bad Request",
                           "501 Not Implemented",
                           "505 HTTP Version Not Supported",
                           "411 Length Required",
                           "431 Request Header Fields Too Large"};
    //puts("HERE3");
    
    int i = 0;
    while(i < 6)
    {
        errormsg.insert(std::pair<int,std::string>(atoi(errors[i].c_str()),msgs[i]));
        i++;
    }
    //puts("HERE4");
    if(status != 0 && status != 200)
    {
        //puts("asa\n");
        ft_creat_file(root,1);
        return;
    }
    else
    {
        //puts("HERE5");
        
        if(locations.size() != 0)
        {
        size_t ns = 0;
        size_t l;
        while (ns < locations.size())
        {
            l=0;
           if (locations[ns].at("location-path") == uri) {
                //std::cout<<ns<<std::endl;
                //std::cout<<locations[ns].at("location-path")<<std::endl;
                l = 1;
                break;
           }
           ns++;
        }
        //puts("HERE6");
       // std::cout<<l<<std::endl;
        if(!l )
        {
            //puts("HERE7");
            status = 404;
            ft_creat_file(root,1);
            //puts("HERE8");
            return;
        }
        /// need check methodes :(
        if(locations[ns].at("allow_methods").empty())
        {
            //puts("HERE9");
            methodes = sv.getMethods();
        }
        else
        {
            //puts("HERE10");
            //std::cout<<"{"<<locations[ns].at("allow_methods")<<"}"<<std::endl;
            char **s = ft_split(locations[ns].at("allow_methods").c_str(),' ');
            l = 0;
            while (s[l])
                methodes.push_back(s[l++]);
            ////need free s
        }
        /////////////////////
        //allowed methodes
        //////////////////
        //puts("HERE11");
        if(allow_methode(req.get_methode()))
        {
            //puts("HERE12");
            status = 405;
            ft_creat_file(root,1);
            return;
        }
        //puts("HERE13");
        if(locations[ns].at("index").empty())
        {
            status = 404;
            ft_creat_file(root,1);
        }
        else
        {
            //puts("HERE14");
            //std::cout<<"{"<<locations[ns].at("index")<<"}"<<std::endl;
            std::string index = root+locations[ns].at("index");
            // std::cout<<index<<std::endl;
            ft_creat_file(index,0);
            index.clear();
            //puts("HERE15");
        }
        ns = 0;
        }
        else
        {
            //puts("HERE16");
            ft_creat_file(root,1);
        }
       // puts("END");         
       // puts("hnaa");
    }
    
                
}
int Response::allow_methode(std::string m)
{
    size_t i = 0;
    //std::cout<< "********** methodes *********" << std::endl;
    while(i < methodes.size())
    {
        
        if(m == methodes[i])
            return (0);
        i++;
    }
    //std::cout<< "********** close methodes *********" << std::endl;
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
    //char ss[3000] = {0};
    if(i != -1 && ok == 0)
    {
        std::ifstream f(root.c_str()); //taking file as inputstream
        std::string str;
        if(f) {
            std::ostringstream ss;
            ss << f.rdbuf(); // reading data
            str = ss.str();
        }
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
        // if(status == 200)
        //     status = 404;
        // //std::ifstream f("/Users/mfagri/Desktop/Webserv/pages/not_found.html");
        // // int i = open("/Users/mfagri/Desktop/Webserv/pages/not_found.html",O_RDWR,777);
        // // read(i,ss,3000);
        // str = ft_generat_html();
        // memset(buf,0,3000);
        // strcpy(buf,"HTTP/1.1 ");
        // strcat(buf,ft_itoa(404));
        // strcat(buf," OK\nDate: Thu, 24 Nov 2022 14:37:49 GMT\nContent-Type: text/html\nContent-Length: "); //9\n\n"
        // int lenght;
        // lenght = str.length();
        // strcat(buf,ft_itoa(lenght));
        // //std::cout<<"lenght:"<<lenght<<std::endl;
        // //std::string v = ft_itoa(lenght);
        // strcat(buf,"\n\n");
        // strcat(buf,(const char *)str.c_str());
        // //std::string final = v+"\n\n"+str;
        // // ft_strlcat(buf,final.c_str(),3000);
        //there is a segfault here to be tested by mfagri
        strcpy(buf,"HTTP/1.1 404 Not found\nContent-Type: text/html\nContent-Length: 13\n\n404 Not found");
    }
    res = buf;
    close(i);
   // std::cout<<res<<std::endl;
}

std::string Response::get_res()
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