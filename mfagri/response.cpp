/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:53:30 by mfagri            #+#    #+#             */
/*   Updated: 2022/11/25 22:32:19 by mfagri           ###   ########.fr       */
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
    printf("{%s}\n",uri.c_str());
    status = req.get_status_code();
    std::string testlocation= "/zoro";
    std::string testmodifier ="^~";
    if(status == 200)
    {
       //location
       //methode
       if(testmodifier == "=")
       {
           if(testlocation == uri)
           {
               std::cout<<"location\n";
           }
       }
       else if(testmodifier == "^~")
       {
           if(strcmp(testlocation.c_str(),uri.c_str()) == 0)
           {
               std::cout<<"per\n";
           }
       }
       else if(testmodifier == "*~")
       {
           if(strcmp(testlocation.c_str(),uri.c_str())== 0)
           {
               /* code */
               std::cout<<"*~\n";
           }
           
       }
       else if(testmodifier == "~")
       {
           if(strcmp(testlocation.c_str(),uri.c_str())== 0)
           {
               /* code */
               std::cout<<"~\n";
           }
       }
    }
    else
    {
        std::cout<<"errors pages";
    }
}