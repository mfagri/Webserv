/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:27:59 by mfagri            #+#    #+#             */
/*   Updated: 2022/12/16 14:42:30 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_info.hpp"

std::string launch_cgi(std::string path,Request Req)
{
    ///wtf
    const char **env;
    int f = fork();
    if(!f)
    {
        execve(path.c_str(),env[0][0],env)
    }
}