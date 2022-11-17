/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:06:56 by mfagri            #+#    #+#             */
/*   Updated: 2022/11/17 23:17:08 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <string>

class Request{
  private:
    std::string request_line;
    std::string methode;///method
    std::string http_version;
    std::string Request_uri;
    ////////////////////////////////
    std::string request_header;
    std::string Transfer_Encoding;//
    std::string host;//host
    std::string Content_Length;//
    std::string Content_Type;//
    std::string User_agent;//maybe
    std::string browser;
    // std::string systype;
    std::string Accept;///
    std::string Accept_Language;///maybe
    std::string Accept_Encoding;///
    std::string Connection;///
    std::string Body;
    //////////////////////////////////
 public:
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