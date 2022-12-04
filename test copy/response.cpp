/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:53:30 by mfagri            #+#    #+#             */
/*   Updated: 2022/12/05 00:32:08 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "response.hpp"
#include "general_info.hpp"

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
Response::Response(Request &req, ServerData sv)
{
    std::vector<std::map<std::string,std::string> > locations = sv.getLocations();
    std::cout<<locations.size()<<std::endl;
    // size_t ns = 0;
    // while (ns < locations.size())
    // {
    //    if (locations[ns].count("index") != 0) {
    //         std::cout<<locations[ns].at("allow_methods")<<std::endl;
    //    }
    //    ns++;
    // }
    uri = req.get_uri();
    reqheaders = req.get_headers();
    status = req.get_status_code();
    std::string errors[7] = {"404","400","501","505","411","431","405"};
    std::string msgs[7] = {"404 Not found",
                           "400 Bad Request",
                           "501 Not Implemented",
                           "505 HTTP Version Not Supported",
                           "411 Length Required",
                           "431 Request Header Fields Too Large",
                           "405 Method Not Allowed"};
    
    int i = 0;
    while(i < 7)
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
    // if(uri.length() == 1)
    //     uri = "/index.html";
    //std::string root = "../links/pages";/////root
    // status = req.get_status_code();
    // root+=uri;
    // if(!allow_methode(req.get_methode()) && status == 200)
    // {
    //     std::cout<<"creat response\n";
    //     ft_creat_file(root,0);
    //     // pos = 1;
    // }
    // else
    //     ft_creat_file(root,1);
    std::string root = sv.getRoot();
    std::vector<std::string> serveename = sv.getServerNames();
    ///methodes in server
    //std::vector <std::string>methodes;
    
    if(status != 200)
    {
        ft_creat_file(root,1);
    }
    else
    {
        
        
        if(locations.size() != 0)
        {
        size_t ns = 0;
        size_t l = 0;
        puts("asa\n");
        while (ns < locations.size())
        {
           if (locations[ns].at("location-path") == uri) {
                //std::cout<<ns<<std::endl;
                //std::cout<<locations[ns].at("location-path")<<std::endl;
                l = 1;
                break;
           }
           ns++;
        }
        if(!l)
        {
            try
            {
            std::cout<<ns<<std::endl;
            std::cout<<"not found\n";
            std::cout<<uri<<std::endl;
            std::cout<<locations[ns].at("location-path")<<std::endl;
                
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
            status = 404;
            ft_creat_file(root,1);
            return;
        }
        /// need check methodes :(
        if(locations[ns].at("allow_methods").empty())
            methodes = sv.getMethods();
        else
        {
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
        if(allow_methode(req.get_methode()))
        {
            status = 405;
            ft_creat_file(root,1);
            return;
        }
        if(locations[ns].at("index").empty())
        {
            status = 404;
            ft_creat_file(root,1);
        }
        else
        {
            //std::cout<<"{"<<locations[ns].at("index")<<"}"<<std::endl;
            std::string index = root+locations[ns].at("index");
            std::cout<<index<<std::endl;
            ft_creat_file(index,0);
            index.clear();
        }
        ns = 0;
        }
        else
            ft_creat_file(root,1);          
       // puts("hnaa");
    }
    
}
int Response::allow_methode(std::string m)
{
    size_t i = 0;
    while(i < methodes.size())
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
        std::string final = v+"\n"+"Connection: close\n"+"\n"+str;
        ft_strlcat(buf,final.c_str(),3000);
        //std::cout<<buf<<std::endl;
    }
    else
    {
        if(status == 200)
            status = 404;
        str = ft_generat_html();
        memset(buf,0,3000);
        strcpy(buf,"HTTP/1.1 ");
        strcat(buf,ft_itoa(status));
        strcat(buf," OK\nDate: Thu, 24 Nov 2022 14:37:49 GMT\nContent-Type: text/html\nContent-Length: "); //9\n\n"
        int lenght;
        lenght = str.length();
        strcat(buf,ft_itoa(lenght));
        strcat(buf,"\n\n");
        strcat(buf,(const char *)str.c_str());
    }
    res = buf;
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