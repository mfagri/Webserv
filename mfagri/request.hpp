/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:06:56 by mfagri            #+#    #+#             */
/*   Updated: 2022/11/23 03:12:56 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>


class Data{
  public:
    std::string file;
    std::string datafile;
    std::string keyvaldata;
  
};

class Request{
  private:
    //////request_line///////
    std::string request_line;
    std::string methode;///method
    std::string Request_uri;//uri
    std::map<std::string,std::string> headers;
    std::map<std::string,std::string> query;
    std::map<std::string,std::string> body_query;
    std::string http_version;//uri
    ////////////////////////////////
    std::string request_header;
    std::string Connection;
    ///////////////////////////////
    std::string Body;
    int chunked;
    //////////////////////////////////
    int status_code;
 public:
    Request();
    Request(char * buf);
    ~Request();
    //////////check methed/////////
    int ft_check_request();
    // void ft_parse_body();
    int get_status_code();
    int parse_request_line(std::string req);
    int parse_headers(std::string headres_);
    int ft_chunked(void);
    int ft_parse_body(void);
    //////////////////////////////
    
};

char	**ft_split(char const *s, char c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
int check_key(char *s);
#endif