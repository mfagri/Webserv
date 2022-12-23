/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:27:59 by mfagri            #+#    #+#             */
/*   Updated: 2022/12/23 17:26:31 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_info.hpp"

std::string	get_cgistring(FILE *temp, int fdtemp)
{
	char buff[4096];
	std::string string;

    rewind(temp);
	while(!feof(temp))
 	{
       if (fgets(buff, 4096, temp) == NULL)
             break;
       string += buff;
 	}
	close(fdtemp);
	fclose(temp);
    return (string);
}

std::string launch_cgi(std::string path,std::string bin ,Request &Req)
{
	std::string			cgistring;
    char *arg[3];
    arg[0] = strdup(bin.c_str()); //pass cgi
    arg[1] = strdup(path.c_str());//path file// char *g = "sdsdsff";
    arg[2] = NULL;
    
    std::map<std::string,std::string> reqheaders = Req.get_headers();
    std::string query = Req.get_queryuri();
    
    std::map<std::string ,std::string > env;
    env["SERVER_NAME"] ="webserv";
    env["HTTP_USER_AGENT"] = reqheaders["User-Agent"];
    env["SERVER_PROTOCOL"] = "HTTP/1.1";
    env["GATEWAY_INTERFACE"] = "CGI/1.1";
    env["REDIRECT_STATUS"] = "200";
    env["PATH_INFO"] = path;
    env["PATH_TRANSLATED"] = path;
    env["SERVER_PORT"] = reqheaders["Host"].substr(reqheaders["Host"].find(":")+1).c_str();//need host
    env["REQUEST_METHOD"] = Req.get_methode();
    env["REQUEST_URI"] = Req.get_uri();
    env["HTTP_HOST"] = reqheaders["Host"];
    env["SCRIPT_NAME"] = Req.get_uri();
    env["SCRIPT_FILENAME"] = path;
    env["CONTENT_TYPE"] = reqheaders["Content-Type"];
    if (reqheaders.count("Cookie"))
    {
       env["HTTP_COOKIE"] = reqheaders.at("Cookie");
    }
    if(Req.get_methode() == "POST")
    {
        env["CONTENT_LENGTH"] = reqheaders["Content-Length"];
    }
    else{
        if(!query.empty())
        {
            env["QUERY_STRING"] = query;
            env["CONTENT_LENGTH"] = "0";
        }
    }
    FILE		*temp = std::tmpfile();
    FILE		*tempo = std::tmpfile();
    int			fdtemp = fileno(temp);
    int			fdtempo = fileno(tempo);
    std::string data ;
    

    std::map<std::string, std::string>::iterator it;
    for (it = env.begin(); it != env.end(); ++it) {
        setenv(it->first.c_str() ,it->second.c_str(), 1);
    }
    int f = fork();
    extern char **environ;
    if(Req.get_methode() == "POST")
    {
        if(dup2(fdtempo,0) < 0)
            std::cout<<"errro\n";
        std::string s = Req.get_body_req();
        s = s.substr(s.find("\r\n\r\n")+4);
        write(fdtempo,s.c_str(),s.length());
        rewind(tempo);
    }
    if(f == 0)
    {
        if(dup2(fdtemp, 1) < 0)
            std::cout<<"errro\n";
        execve(arg[0],arg,environ);
        exit(0);
    }
    else
    {
        waitpid(-1,NULL,0);
        cgistring = get_cgistring(temp,fdtemp);
    }
    free(arg[0]);
    free(arg[1]);
    unsetenv("QUERY_STRING");
    return (cgistring);
}