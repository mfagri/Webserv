/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:53:17 by mfagri            #+#    #+#             */
/*   Updated: 2022/11/26 19:01:37 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "request.hpp"
class Request;

class Response{
    private:
        std::string uri;
        char * res;
        int status;
    public:
        Response();
        Response(Request &req);
        void ft_creat_file(std::string root,int ok);
        char * get_res();
};
int find_option(char *s[],std::string op);
#endif