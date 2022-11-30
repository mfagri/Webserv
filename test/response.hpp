/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:53:17 by mfagri            #+#    #+#             */
/*   Updated: 2022/11/27 17:25:58 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "general_info.hpp"
class Request;

class Response{
    private:
        std::string uri;
        char * res;
        int status;
        std::map<std::string,std::string>reqheaders;
        std::map<int,std::string>errormsg;
    public:
        Response();
        Response(Request &req);
        void ft_creat_file(std::string root,int ok);
        char * get_res();
        char *ft_generat_html();
        int allow_methode(std::string m);
};
int find_option(char *s[],std::string op);
#endif