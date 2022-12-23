/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_info.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntanjaou <ntanjaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:12:09 by ntanjaou          #+#    #+#             */
/*   Updated: 2022/12/23 19:12:11 by ntanjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_INFO
#define GENERAL_INFO

#include <exception>
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <arpa/inet.h>
#include <cstdio>
#include <dirent.h>
#include <cstdlib>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/poll.h>
#include <fcntl.h>
#include <fstream>
#include <limits.h>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <cstring>

#include "ServerData.hpp"
#include "requestData.hpp"
#include "Parser.hpp"
#include "request.hpp"
#include "response.hpp"
#include "socket.hpp"
#include "server.hpp"

#define BUFFSIZE 3000
std::string launch_cgi(std::string path,std::string bin ,Request &Req);
#endif