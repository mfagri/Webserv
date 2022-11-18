/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:06:56 by mfagri            #+#    #+#             */
/*   Updated: 2022/11/18 21:04:00 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <string>
#include <map>

class Request{
  private:
    //////request_line///////
    std::string request_line;
    std::string methode;///method
    std::string Request_uri;//uri
    std::map<std::string,std::string> headers;
    float http_version;//uri
    ////////////////////////////////
    std::string request_header;
    ///////////////////////////////
    std::string Body;
    //////////////////////////////////
    int status_code;
 public:
    Request();
    Request(char * buf);
    ~Request();
    //////////check methed/////////
    int ft_check_request();
    void ft_parse_body();
    //////////////////////////////
    
};

char	**ft_split(char const *s, char c);

#endif