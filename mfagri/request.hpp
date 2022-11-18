/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:06:56 by mfagri            #+#    #+#             */
/*   Updated: 2022/11/18 20:29:49 by mfagri           ###   ########.fr       */
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
    float http_version;//uri
    ////////////////////////////////
    std::string request_header;
    ///////////////////////////////
    std::string Body;
    //////////////////////////////////
 public:
    std::map<std::string,std::string> headers;
    Request();
    Request(char * buf);
    ~Request();
    void get_methode();
    void get_header();
    //////////check methed/////////
    int ft_check_request();
    //////////////////////////////
    void print_request();
    
};

char	**ft_split(char const *s, char c);

#endif