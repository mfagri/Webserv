/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:53:30 by mfagri            #+#    #+#             */
/*   Updated: 2022/12/26 17:48:14 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"
#include "general_info.hpp"
# include <filesystem>

Response::Response()
{
   
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
}
Response::Response(Request &req, std::vector<ServerData> servers)
{
    reqheaders = req.get_headers();
    status = req.get_status_code();
    ServerData sv;
    int port = atoi(reqheaders["Host"].substr(reqheaders["Host"].find(":")+1).c_str());
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
    error_path = sv.getErrorPages();
    std::vector<std::string> v =  sv.getServerNames();
    server_name = v[0];
    std::vector<std::map<std::string,std::string> > locations = sv.getLocations();
    uri = req.get_uri();
    std::string temp;
    size_t tt  =0 ;
    while(uri[tt])
    {
        if(uri[tt] == '?')
            break;
        temp += uri[tt];
        tt++;
    }
    uri.clear();
    uri = temp;
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

    size_t i = 0;
    while(i < 11)
    {
        errormsg.insert(std::pair<int,std::string>(std::stoi(errors[i].c_str()),msgs[i]));
        i++;
    }
        if(status != 200)
        {
        
            ft_creat_file(root,1);
            return;
        }
    if(req.get_methode() == "GET" || req.get_methode() == "POST")
    {
       if(1)
        {
            size_t ns = 0;
            int l = 0;
            std::string url = get_location_uri(uri);
            if (strrchr(uri.c_str(), '.'))
            {
                std::string cgis = strrchr(uri.c_str(), '.');
                if (cgis == ".py" || cgis == ".php")
                {
                    
                    cgis = "*" + cgis;
                    i = 0;
                    while (i < locations.size())
                    {
                            if (locations[i].at("location-path") == cgis)
                            {
                                _cgi = true;
                                if(locations[i].at("methods").empty())
                                {
                                    methodes = sv.getMethods();
                                }
                                else
                                {
                                    char **s = ft_split(locations[i].at("methods").c_str(),' ');
                                    l = 0;
                                    while (s[l])
                                        methodes.push_back(s[l++]);
                                    ft_free2(s);
                                }
                                if(allow_methode(req.get_methode()))
                                {
                                    status = 405;
                                    ft_creat_file(root,1);
                                    return;
                                }
                                 
                            uri = strrchr(uri.c_str(),'/');
                            std::string output;
                            std::string bin =  locations[i].at("cgi_bin");
                            std::string path = locations[i].at("root")+ uri;
                            if(access(path.c_str(), R_OK) == 0)
                            {
                                output =  launch_cgi(path,bin,req);
                                ft_creat_file(output,0);
                            }
                            else
                            {
                               status = 404;
                               ft_creat_file(output,1); 
                            }
                            return;
                        }
                        i++;
                    }
                    i = 0;
                }
            }
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
                DIR* d = opendir(file.c_str());
                if(d)
                {
                    closedir(d);
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
                for (size_t i = 0; i < locations.size(); i++)
                {
                    if(locations[i].at("location-path") == url)
                    {
                        if(locations[i].at("methods").empty())
                        {
                            methodes = sv.getMethods();
                        }
                        else
                        {
                            char **s = ft_split(locations[i].at("methods").c_str(),' ');
                            l = 0;
                            while (s[l])
                                methodes.push_back(s[l++]);
                            ft_free2(s);
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
                            std::string ret = locations[i].at("return").substr(locations[i].at("return").find("/"));
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
        std::string deleteroot;
        size_t j = 0;
        std::string is_allow = get_location_uri(uri);
        while(j < locations.size())
        {
            if (locations[j].at("location-path") == "/upload")
            {
                deleteroot = locations[j].at("root");
                break;
            }
            j++;
        }
        if(is_allow != "/upload")
        {
            status = 409;
            ft_creat_file("bad",1);
            return;
        }
        std::string h  = strrchr((char *)uri.c_str(),'/');
        h = deleteroot+h;
        DIR* d = opendir(h.c_str());
        if(d != NULL)
        {
            closedir(d);
            status = 401;
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

std::string Response::getExtension(std::string path) {
    
    std::string ex;
    int s = path.length() - 1;
    while (s >= 0 && path[s] != '.')
    {
        ex.insert(0,1,path[s]);
        s--;
    }
    return ex;
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
    dirent *dent = NULL;

    dir = opendir(root.c_str());// this part
    std::string body = "<!DOCTYPE html>\n\
                        <html lang=\"en\">\n\
                        <style> \
                        @import url('https://fonts.googleapis.com/css2?family=Inter:wght@400;600;700&family=Montserrat:wght@500&display=swap'); \
                        * {	\
                            font-size:20px; \
                        } \
                        ul { \
                            border-top: solid black 1px; \
                            border-bottom: solid black 1px; \
                            margin:50px; \
                            padding:150px;\
                        } \
                        li{ \
                            list-style:none; \
                            margin:30px; \
                        } li a{ \
                            text-decoration:none; \
                            color:black; \
                        } \
                        li { \
                            display: flex; \
                        } \
                        img { \
                          width:25px;  \
                          height: 25px; \
                          margin-right: 5px; \
                        }\
                        </style>\n\
                        <head>\n\
                            <meta charset =\"UTF-8\">\n\
	                        <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n\
                        	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n\
                            <script src=\"https://kit.fontawesome.com/cb1896687a.js\" crossorigin=\"anonymous\"></script>\n\
                        	<title>Root</title>\n\
                        </head>\n\
                        <body>\n\
                       <ul> ";
    if (dir != NULL)
    {
       while ((dent = readdir(dir)) != NULL) {
            std::string url;
            std::string icon;
            std::string fname = dent->d_name;
            if (uri[0] == '/' && uri.length() == 1)   
                url =  fname;
            else 
                url = uri + "/" + fname;
            if (fname != "." && fname != "..") {
                std::string url1 = root + "/" + fname;
                DIR *d2 = opendir(url1.c_str());
                if (d2){
                    icon = "<img src=\"https://cdn-icons-png.flaticon.com/512/3767/3767084.png\" />";
                closedir(d2); 
                }
                else
                    icon = "<img src=\"https://cdn-icons-png.flaticon.com/512/2965/2965335.png\" />";
                std::string str = "\n<li>" + icon + "<a href=\"" + url + "\">" + fname + "</a></li>\n";
                body.append(str);
            }
       }
        closedir(dir);
    }
    body.append("	</ul>\n\
                    </body>\n\
                    </html>");
    return body;
}
void Response::ft_creat_file(std::string root,int ok)
{
    std::string buf;
    int i = open(root.c_str(),O_RDWR);
    std::string str;
    if (_cgi && ok == 0)
    {
       std::string hd;
       if (root.find("\r\n\r\n") != std::string::npos)
       {
            hd = root.substr(0, root.find("\r\n\r\n"));
       }
       time_t now = time(0); // get current dat/time with respect to system
       char *dt = ctime(&now);
       buf.append("HTTP/1.1 ");
       if (hd.find("Status: 301 Moved Permanently") != std::string::npos)
            buf.append("301 Moved Permanently");
       else
            buf.append(std::to_string(status));
       buf.append("\n");
       buf.append(hd);
       buf.append(" OK");
       buf.append("\nServer: ");
       buf.append(server_name);
       buf.append("\nDate: ");
       buf.append(dt);
       buf.append("Content-Type: text/html\nContent-Length: ");
       int lenght;
       lenght = root.length();
       buf.append(std::to_string(lenght));
       buf.append("\n\n");
       if (root.find("\r\n\r\n") != std::string::npos)
            root = root.substr(root.find("\r\n\r\n") + 4);
       buf.append(root);
       res = buf;
       return;
    }
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
        buf.append(std::to_string(status));
        buf.append(" OK");
        buf.append("\nServer: ");
        buf.append(server_name);
        buf.append("\nDate: ");
        buf.append(dt);
        std::string st =  getExtension(root);
        std::string rep = "Content-Type: $1\nContent-Length: ";
        rep.replace(14,2,add_content_type(st));
        buf.append(rep); //9\n\n"
        int lenght;
        lenght = str.length();
        buf.append(std::to_string(lenght));
        buf.append("\n\n");
        buf.append(str);
        res = buf;

        close(i);
        return;
    }
    else if (_autoindex)
    {  
        DIR* d = opendir(root.c_str());
        if (d != NULL)
        {
        std::string str;
        time_t now = time(0); // get current dat/time with respect to system
        std::string dt = ctime(&now);
        buf.append("HTTP/1.1 ");
        buf.append(std::to_string(status));
        buf.append(" OK");
        buf.append("\nServer: ");
        buf.append(server_name);
        buf.append("\nDate: ");
        buf.append(dt);
        std::string rep = "Content-Type: text/html\nContent-Length: ";
        std::string body = getAutoIndexBody(root);
        buf.append(rep);
        buf.append(std::to_string(body.length()));
        buf.append("\n\n");
        buf.append(body);
        res = buf;
        close(i);
        closedir(d);
        return;
        }
    }
    else
    {
        if(status == 301)
        {
            res = "HTTP/1.1 301 Moved Permanently\nLocation: ";
            res.append(root);
            res.append("\n");
            return;
        }
        if(status == 200)
            status = 404;
        std::string errorpage = error_path;
        errorpage += std::to_string(status);
        errorpage += ".html";
        std::ifstream f(errorpage.c_str());
        std::string str;
        if(f) {
            std::ostringstream ss;
            ss << f.rdbuf(); // reading data
            str = ss.str();
        }
        time_t now = time(0); // get current dat/time with respect to system
        std::string dt = ctime(&now);
        buf.append("HTTP/1.1 ");
        buf.append(errormsg[status]);
        buf.append("\nServer: ");
        buf.append(server_name);
        buf.append("\nDate: ");
        buf.append(dt);
        buf.append("Content-Type: text/html\nContent-Length: ");
        buf.append(std::to_string(str.length()));//length
        buf.append("\n\n");
        buf.append(str);//body
        res = buf;
        close(i);
        return;
    }
}

std::string Response::get_res()
{
    return res;
}
