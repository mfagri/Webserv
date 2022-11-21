/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 23:00:22 by mmardi            #+#    #+#             */
/*   Updated: 2022/11/21 01:44:26 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ServerData.hpp"

ServerData::ServerData() {
	port = 80;
	host = "0.0.0.0";
}

void ServerData::setData(std::map<std::string, std::string> server) {
	
	try
	{
		std ::string hp = server.at("listen");
		if (strrchr(hp.c_str(), ':')) {
			char *h = strtok((char *)hp.c_str(), ":");
			char *p = strtok(NULL, ":");
			if (!p  || !h) {
				std::cerr << "bad host::port";
				exit (1);
			}
			port = std::stoi(p);
			host = h;
		}
		
	}
	catch(const std::exception& e)
	{
	}
	
}

std::string ServerData::getHost(void) {
	return host;
}

int ServerData::getPort() {
	return port;
}

ServerData::~ServerData() {}