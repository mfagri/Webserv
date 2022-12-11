/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:53:30 by mfagri            #+#    #+#             */
/*   Updated: 2022/12/11 03:49:18 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"
# include <filesystem>

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
;
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
   
    // close(dir);
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
    if(status != 200)
    {
 
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

            status = 405;
            ft_creat_file(root,1);
            return;
        }
        //puts("HERE13");
        if (locations[ns].count("autoindex")) {
            if (locations[ns].at("autoindex") == "on") { 
                _autoindex = true;
            }
        }
        if(locations[ns].count("index") == 0 && !_autoindex)
        {

            status = 404;
            ft_creat_file(root,1);
            return ;
        }
        else
        {
            puts("HERE14");

            // std::cout<<"{"<<locations[ns].at("index")<<"}"<<std::endl;
            if(!_autoindex)
            {
            std::string index = root+locations[ns].at("index");
            ft_creat_file(index,0);
            index.clear();
            }
            else
                ft_creat_file(root,0);
            //puts("HERE15");
        }
        ns = 0;
        }
        else
        {
            puts("HERE16");
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
std::string add_content_type(std::string type)
{

    if(type == "png" || type == "jpeg" || type == "jpj" || type == "ico")
       return ("image/"+type);
    else if(type == "html" || type == "txt" || type == "htm" || type == "css")
       return ("text/"+type);
    else if (type == "json")
        return "application/json";
    return ("text/html");
        
}

std::string getAutoIndexBody(std::string root) {
    // DIR *dir;
    // struct dirent *dent;
    // dir = opendir(root.c_str());// this part
    std::ifstream FILE("/home/mmardi/Desktop/webserv/links/htmlfiles/autoindex.html");
    std::cout << root ;
    std::string body = "3aa";
    size_t index;
    if (FILE)
    {
        std::ostringstream ss;
        ss << FILE.rdbuf(); // reading data
       body = ss.str();
    }
    index = body.find("<ul>", 0);
    // index += 4;
    // if (dir != NULL)
    // {
    //    dent = readdir(dir);
        std::string element = "\n<li><a href=\""+root+"\">here</a></li>\n";
       body.insert(index, element);

       // while ((dent = readdir(dir)) != NULL) {

       // }
        
    // }
    std::cout << "------" << body;
    return body;
}
void Response::ft_creat_file(std::string root,int ok)
{
    std::string buf;
    //char *infile;
    int i = open(root.c_str(),O_RDWR);
    std::cout << root << i <<std:: endl;
    std::string str;
    //char ss[3000] = {0};
    if (_autoindex)
    {  
        std::string str;
        time_t now = time(0); // get current dat/time with respect to system
        char *dt = ctime(&now);
        buf.append("HTTP/1.1 ");
        buf.append(ft_itoa(status));
        buf.append(" OK\nDate: ");
        buf.append(dt);
        std::string rep = "Content-Type: text/html\nContent-Length: ";
        buf.append(rep);
        std::string body = getAutoIndexBody(root);
        buf.append(ft_itoa(body.length()));
        buf.append("\n\n");
        buf.append(body);
        }
    else if(i != -1 && ok == 0)
    {
        std::ifstream f(root.c_str()); //taking file as inputstream
        std::string str;
        if(f) {
            std::ostringstream ss;
            ss << f.rdbuf(); // reading data
            str = ss.str();
        }
        //memset(buf,0,3000);
        // strcpy(buf,"HTTP/1.1 ");
        time_t now = time(0); // get current dat/time with respect to system  
  
        char* dt = ctime(&now); // convert it into string  
        buf.append("HTTP/1.1 ");
        buf.append(ft_itoa(status));
        buf.append(" OK\nDate: ");
        buf.append(dt);
        strtok((char*)root.c_str(), ".");
        std::string st=  strtok(NULL, ".");
        std::string rep = "Content-Type: $1\nContent-Length: ";
        rep.replace(14,2,add_content_type(st));
        std::cout << rep << std::endl;
        buf.append(rep); //9\n\n"
        int lenght;
        lenght = str.length();
        //std::cout<<"lenght:"<<lenght<<std::endl;
        // std::string v = ft_itoa(lenght);
        // std::string final = v+"\n\n"+str;
        buf.append(ft_itoa(lenght));
        buf.append("\n\n");
        buf.append(str);
        // std::cout << buf << std::endl;
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
        buf.append("HTTP/1.1 404 Not found\nContent-Type: text/html\nContent-Length: 13\n\n404 Not found");
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