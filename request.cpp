/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:06:24 by mfagri            #+#    #+#             */
/*   Updated: 2022/11/14 22:33:35 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request.hpp"
/// methods// post | get | delete | connect | put
Request::Request()
{
    
};

Request::Request(char *buf)
{
    std::cout<<"request class\n";
    char **t;
    t = ft_split(buf,'\n');
    request_line = t[0];
    int i = 0;
    while(t[i])
        std::cout<<t[i++]<<std::endl;
};

Request::~Request()
{
    
};

void Request::get_methode()
{
    
}

