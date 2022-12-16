/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:27:59 by mfagri            #+#    #+#             */
/*   Updated: 2022/12/16 21:52:32 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_info.hpp"



// CIG (Common Gateway Interface) enables web servers to execute an external program, for example to process user request.

// Those programs requires additionnal informations (passed as environnement variables) to be executed. In return they provide all the informations needed by the server to respond to the client.

// Our server should be able to specify which URLs should be handled by a specific CGI (cf location *.php { cgi_pass CGI_PATH } blocks).

// As mentionned in the subject, we can fork to execute the CGI.

// execve(CGI_PATH, args, env);
// where env is filled as above.

// Server specific variables :

// SERVER_SOFTWARE : name/version of HTTP server.
// SERVER_NAME : host name of the server, may be dot-decimal IP address.
// GATEWAY_INTERFACE : CGI/version. CGI/1.1
// Request specific variables :

// SERVER_PROTOCOL : HTTP/version.
// SERVER_PORT : TCP port (decimal).
// REQUEST_METHOD : name of HTTP method (see above)
// PATH_INFO : path suffix, if appended to URL after program name and a slash
// PATH_TRANSLATED : corresponding full path as supposed by server, if PATH_INFO is present.
// SCRIPT_NAME : relative path to the program, like /cgi-bin/script.cgi.
// QUERY_STRING : the part of URL after ? character
// REMOTE_HOST : host name of the client, unset if server did not perform such lookup
// REMOTE_ADDR : IP address of the client (dot-decimal)
// AUTH_TYPE : identification type, if applicable
// REMOTE_USER : used for certain AUTH_TYPEs
// REMOTE_IDENT : see ident, only if server performed such lookup.
// CONTENT_TYPE : Internet media type of input data if PUT or POST method are used, as provided via HTTP header
// CONTENT_LENGTH : similarly, size of input data (decimal, in octets) if provided via HTTP header
// Variables passed by user agent (HTTP_ACCEPT, HTTP_ACCEPT_LANGUAGE, HTTP_USER_AGENT, HTTP_COOKIE and possibly others) contain values of corresponding HTTP headers and therefore have the same sense.
// Convention : we should have a cgi-bin directory in our root

// Uploading files could be handled by CGI (for example php)


/////////////////////////////////////////////////////
// QUERY_STRING: The query string from the URL, if any.
// REQUEST_METHOD: The HTTP method used to request the CGI program (e.g. "GET", "POST", etc.)
// CONTENT_TYPE: The MIME type of the request body, if any.
// CONTENT_LENGTH: The length of the request body, if any.
// HTTP_USER_AGENT: The user agent string from the client's browser.
// HTTP_REFERER: The URL of the page that referred the client to the CGI program.
// REMOTE_ADDR: The IP address of the client.
// SERVER_NAME: The hostname of the server.
// SERVER_SOFTWARE: The name and version of the web server software.
////////////////
std::string launch_cgi(std::string path,Request Req)
{
    ///wtf

    (void)path;
	// std::string			string;
	// HTTPResponse		&response = client.getResponse();
	// HTTPHeader			&header = client.getHeader();
	// std::string			file = sock.getRealUrl(sockNbr, response.getUrl());
    

	// client.setEnvValue("PATH_INFO", file);
	// client.setEnvValue("SCRIPT_FILENAME", file);
	// client.setEnvValue("REDIRECT_STATUS", "200");
	// if (header.getContentType() == "")
	// 	client.setEnvValue("CONTENT_TYPE", "application/x-www-form-urlencoded");
	// else
	// 	client.setEnvValue("CONTENT_TYPE", header.getContentType());
	// if (client.getEnvValue("REQUEST_METHOD") == "POST")
	// 	client.setEnvValue("CONTENT_LENGTH", toString(client.getBodySize()));
	// else
	// {
	// 	if (client.isQueryString() == false)
	// 		client.setEnvValue("QUERY_STRING", "");
	// }
    char **envcgi;
    char *arg[3];
    int fd  = open("tet",O_CREAT| O_RDWR,777);
    arg[0] = strdup("/usr/bin/python3"); //pass cgi
    arg[1] = strdup("../links/htmlfiles/c.py");//path file
    arg[2] = NULL;
    
    std::map<std::string,std::string> reqheaders = Req.get_headers();
    std::string query = Req.get_queryuri();
    
    std::map<std::string ,std::string > env;
    env["SERVER_NAME"] ="webserv";
    env["SERVER_PROTOCOL"] = "HTTP/1.1";
    env["GATEWAY_INTERFACE"] = "CGI/1.1";
    env["SERVER_PORT"] = atoi(reqheaders["Host"].substr(reqheaders["Host"].find(":")+1).c_str());;//need host
    env["REQUEST_METHOD"] = Req.get_methode();
    env["REQUEST_URI"] = Req.get_uri();
    env["SCRIPT_NAME"] = Req.get_uri();
    if(Req.get_methode() == "POST")
        env["CONTENT_LENGTH"] = reqheaders["CONTENT_LENGTH"];
    else{
        if(!query.empty())
            env["QUERY_STRING"] = query;
    }
    env["CONTENT_TYPE"] = reqheaders["CONTENT_TYPE"];
   // env["REMOTE_ADDR"] = "";
    //env["AUTH_TYPE"] = "";
    size_t i  = env.size();
    envcgi =(char **) malloc(sizeof(char *) * i+1);
    std::map<std::string, std::string>::iterator it;
    i  = 0;
    for (it = env.begin(); it != env.end(); ++it) {
      std::string hh;
      hh = it->first + "=" + it->second;
       envcgi[i++] = strdup(hh.c_str());
    }
    envcgi[i] = NULL;
    int f = fork();
   // std::cout<<path<<std::endl;
    dup2(fd,1);
    if(!f)
    {
        execve(arg[0],&arg[0],envcgi);
        exit(0);
    }
    dup2(1,fd);
    // char buf[1024];
    // read(fd,buf,1024);
    // std::cout<<"{"<<buf<<"}"<<std::endl;
    close(fd);
    return ("ss");
}