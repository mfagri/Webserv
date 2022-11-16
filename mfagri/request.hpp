/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:06:56 by mfagri            #+#    #+#             */
/*   Updated: 2022/11/16 02:31:04 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <string>

class Request{
  private:
    std::string request_line;
    std::string methode;
    std::string http_version;
    std::string Request_uri;
    ////////////////////////////////
    std::string request_header;
    std::string host;
    std::string User_agent;
    std::string Accept_Language;
    std::string Accept_Encoding;
    std::string Connection;
 public:
    Request();
    Request(char * buf);
    ~Request();
    void get_methode();
    void get_header();
    
};
char	**ft_split(char const *s, char c);

#endif