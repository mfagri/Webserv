/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:53:17 by mfagri            #+#    #+#             */
/*   Updated: 2022/12/11 19:03:38 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "general_info.hpp"
class Request;

class Response{
    private:
        std::string uri;
        std::string res;
        std::string autoindex;
        bool _autoindex;
        int status;
        std::map<std::string,std::string>reqheaders;
        std::map<int,std::string>errormsg;
        std::vector <std::string>methodes;
    public:
        Response();
        
        ~Response();
        Response(Request &req, std::vector<ServerData> servers);
        void ft_creat_file(std::string root,int ok);
        std::string get_res();
        char *ft_generat_html();
        int allow_methode(std::string m);
        std::string getAutoIndexBody(std::string root);
};
int find_option(char *s[],std::string op);
#endif