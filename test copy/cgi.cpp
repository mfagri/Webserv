/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:27:59 by mfagri            #+#    #+#             */
/*   Updated: 2022/12/14 17:57:37 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_info.hpp"

std::string launch_cgi(std::string path,Request Req)
{
    ///wtf
    char **env;
    int f = fork();
    if(!f)
    {
        execve(path.c_str(),env[0][0],env)
    }
}