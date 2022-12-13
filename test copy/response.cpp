/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:53:30 by mfagri            #+#    #+#             */
/*   Updated: 2022/12/13 21:33:29 by mmardi           ###   ########.fr       */
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
std::string get_location_uri(std::string uri)
{
    std::string s;
    size_t i = 0;
    if(uri[0] == '/')
        i++;
    while(uri[i] != '/' && i < uri.length())
    {
        s += uri[i];
        i++;
    }
    return ("/"+s);
}
Response::~Response()
{
    //bzero(res.c_str(),strlen(res)); 
}
Response::Response(Request &req, std::vector<ServerData> servers)
{
    reqheaders = req.get_headers();
    status = req.get_status_code();
    //\std::cout<<status<<std::endl;
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
    std::string root = sv.getRoot();
    std::vector<std::map<std::string,std::string> > locations = sv.getLocations();
    uri = req.get_uri();
    //std::cout << uri<<std::endl;
    std::string errors[11] = {"404","400","501","505","411","431","405","409","202","204","401"};
    std::string msgs[11] = {"404 Not found",
                           "400 Bad Request",
                           "501 Not Implemented",
                           "505 HTTP Version Not Supported",
                           "411 Length Required",
                           "431 Request Header Fields Too Large",
                           "405 Method Not Allowed",
                           "409 Conflict",
                           "202 Accepted",
                           "204 No Content",
                           "401 Unauthorized"
                           };

    int i = 0;
    while(i < 11)
    {
        errormsg.insert(std::pair<int,std::string>(atoi(errors[i].c_str()),msgs[i]));
        i++;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    if(req.get_methode() == "GET" || req.get_methode() == "POST")
    {
        if(status != 200)
        {
        
            ft_creat_file(root,1);
            return;
        }
        else
        {
            size_t ns = 0;
            int l = 0;
            std::string url = get_location_uri(uri);
            //std::cout<<"-------"+url<<std::endl;
            while (ns < locations.size())
            {
                l = 0;
               if (locations[ns].at("location-path") == url){
                    l = 1;
                    break;
               }
               ns++;
            }
            if(!l)
            {
                std::string file = root + uri;
                //std::cout << file << std::endl;               
                if(opendir(file.c_str()))
                {
                    _autoindex = true;
                    ft_creat_file(file,0);
                    return;
                    
                }
                if(access(file.c_str(), F_OK) == 0)
                {
                    ft_creat_file(file,0);
                    return ;
                }
                ft_creat_file(file,0);
                return;
            }
            else
            {
                
                std::string uri1 = uri;
                std::string url = get_location_uri(uri1);
                int index = uri1.find(url, 0); 
                uri1.erase(index, url.length());
                //std::cout <<"{" +url+"}" <<  std::endl;
                for (size_t i = 0; i < locations.size(); i++)
                {
                    if(locations[i].at("location-path") == url)
                    {
                       // std::cout << locations[i].at("root")+uri1 << std::endl;
                        if(locations[i].at("allow_methods").empty())
                        {
                            methodes = sv.getMethods();
                        }
                        else
                        {
                            char **s = ft_split(locations[i].at("allow_methods").c_str(),' ');
                            l = 0;
                            while (s[l])
                                methodes.push_back(s[l++]);
                        }
                        if(allow_methode(req.get_methode()))
                        {
                            status = 405;
                            ft_creat_file(root,1);
                            return;
                        } 
                        if(locations[i].count("return"))
                        {
                            status = 301;
                            std::cout << "ssd";
                            std::string ret = locations[i].at("return").substr(locations[i].at("return").find("/"));
                            std::cout<<ret<<std::endl;
                            ft_creat_file(ret,1);
                            return;
                        }  
                        if (locations[i].count("autoindex")) {
                            if (locations[i].at("autoindex") == "on"){
                                _autoindex = true;
                            }
                        }
                        if (locations[i].count("index") && !_autoindex)
                                uri1 += "/" +locations[i].at("index");
                        
                        ft_creat_file(locations[i].at("root")+uri1,0);
                        break;
                    }
                }
                
            }
        }
    }
    else
    {
        std::string is_allow = get_location_uri(uri);
        //  std::cout<<root<<std::endl;
        //  std::cout<<uri<<std::endl;
        if(is_allow != "/upload")
        {
            status = 409;
            ft_creat_file("bad",1);
            return;
        }
        std::string h = root + uri;
        if(opendir(h.c_str()) != NULL)
        {
            status = 401;
            //401 Unauthorized
            ft_creat_file("bad",1);
            return;
        }
        else
        {
            if(remove(h.c_str()) == 0)
            {
                status = 202;
                ft_creat_file("good",1);//202 Accepted
            }
            else
            {
                status = 204;
                ft_creat_file("bad",1);//204 No Content
            }
            return;
        }
        // std::cout<<h<<std::endl;
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
std::string add_content_type(std::string type)
{

    if(type == "png" || type == "jpeg" || type == "jpj")
       return ("image/"+type);
    else if (type == "ico")
        return ("text/x-icon");
    else if(type == "html" || type == "txt" || type == "htm" || type == "css")
       return ("text/"+type);
    else if (type == "json" || type == "pdf")
        return "application/"+type;
        else if (type == "mp4")
        return "video/mp4";
    return ("text/plain");
        
}

std::string Response::getAutoIndexBody(std::string root) {
    DIR *dir;
    struct dirent *dent;
    dir = opendir(root.c_str());// this part
    // std::cout << root ;
    std::string body = "<!DOCTYPE html>\n\
                        <html lang=\"en\">\n\
                        <style>ul{background-color: cyan; margin:50px; padding:150px}li{list-style:none; margin:30px;} li a{text-decoration:none; color:black;}</style>\n\
                        <head>\n\
            	            <meta charset=\"UTF-8\">\n\
	                <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n\
                        	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n\
                        	<title>Root</title>\n\
                        </head>\n\
                     <body>\n\
	                      <ul>";
    if (dir != NULL)
    {
       while ((dent = readdir(dir)) != NULL) {
            std::string url;
            std::string fname = dent->d_name;
            if (uri[0] == '/' && uri.length() == 1)   
                url = fname;
            else 
                url = uri + "/" + fname;
            if (fname != "." && fname != "..") {
                std::string str= "\n<h1><a href=\"" + url +"\">" + fname +"</a></h1>\n";
                body.append(str);
            }
       }
        
    }
    body.append("	</ul>\n\
                    </body>\n\
                    </html>");
   // std::cout << body << std::endl;
    return body;
}
void Response::ft_creat_file(std::string root,int ok)
{
    std::string buf;
    int i = open(root.c_str(),O_RDWR);
    //std::cout << root << i <<std:: endl;
    std::string str;
    if(i != -1 && ok == 0)
    {
        std::ifstream f(root.c_str()); //taking file as inputstream
        std::string str;
        if(f) {
            std::ostringstream ss;
            ss << f.rdbuf(); // reading data
            str = ss.str();
        }
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
        //std::cout << rep << std::endl;
        buf.append(rep); //9\n\n"
        int lenght;
        lenght = str.length();
        buf.append(ft_itoa(lenght));
        buf.append("\n\n");
        buf.append(str);
        res = buf;
        close(i);
        return;
    }
    else if (_autoindex && opendir(root.c_str()))
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
        body.clear();
        res = buf;
        close(i);
        return;
    }
    else
    {
        if(status == 301)
        {
            puts("imhere");
            res = "HTTP/1.1 301 Moved Permanently\nLocation: ";
            res.append(root);
            res.append("\n");
            // res.append("\r\n\r\n\r\n");
            return;
        }
        if(status == 200)
            status = 404;
        // std::ifstream f(); //taking file as inputstream
        // std::string str;
        // if(f) {
        //     std::ostringstream ss;
        //     ss << f.rdbuf(); // reading data
        //     str = ss.str();
        // }
        time_t now = time(0); // get current dat/time with respect to system
        char *dt = ctime(&now);
        buf.append("HTTP/1.1 ");
        buf.append(errormsg[status]);
        buf.append("\nDate: ");
        buf.append(dt);
        buf.append("Content-Type: text/html\nContent-Length: ");
        buf.append(ft_itoa(errormsg[status].length()));//length
        buf.append("\n\n");
        buf.append(errormsg[status]);//body
        res = buf;
        close(i);
        return;
    }
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