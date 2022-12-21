/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:27:59 by mfagri            #+#    #+#             */
/*   Updated: 2022/12/21 21:10:48 by mfagri           ###   ########.fr       */
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
    //std::cout<<"{"<<string<<"}";
    return (string);
	// client.setIsContentLen(string);
	// client.setCgiBody(string);
}

std::string launch_cgi(std::string path,std::string bin ,Request &Req)
{
    ///wtf

    // (void)path;
    // (void)bin;
	std::string			cgistring;
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
    // char **envcgi;
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
    if(Req.get_methode() == "POST")
    {
        env["CONTENT_LENGTH"] = reqheaders["Content-Length"];
        // if(env["Content-Type"] == "application/x-www-form-urlencoded")
        //     env["QUERY_STRING"] = Req.get_body_req();
    }
    else{
        if(!query.empty())
        {
            env["QUERY_STRING"] = query;
            //std::cout<<env["QUERY_STRING"]<<std::endl;
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
    if(cgistring.find("\r\n\r\n") != std::string::npos)
        cgistring = cgistring.substr(cgistring.find("\r\n\r\n")+4);
    //std::cout<<"["<<cgistring<<"]"<<std::endl;
    return (cgistring);
}