/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 23:00:22 by mmardi            #+#    #+#             */
/*   Updated: 2022/11/21 17:46:16 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ServerData.hpp"

ServerData::ServerData() {
	port = 80;
	host = "0.0.0.0";
	body_size = 1024;
}

void ServerData::setData(std::map<std::string, std::string> server) {
	
	if (server.count("listen") > 0) {
		std::string hp = server.at("listen");
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
	if (server.count("server_name") > 0) {
		std::string names = server.at("server_name");
		char *name = strtok((char *)names.c_str(), " ");
		while (name)
		{
			server_names.push_back(name);
			name = strtok(NULL, " ");
		}
		std::cout << server_names.size() << std::endl;
		std::cout << server_names[1] << std::endl;
	}
	if (server.count("body_size") > 0) {
		try
		{
			body_size = std::stoi(server.at("body_size"));
		}
		catch(const std::exception& e)
		{
			std::cerr << "Number expected in body_size value" << '\n';
			exit (1);
		}
	}
	if (server.count("methods") > 0) {
		std::string m = server.at("methods");
		char *method = strtok((char *)m.c_str(), ",");
		while (method) {
			methods.push_back(method);
			method = strtok(NULL, ",");
		}
	}
}

std::string ServerData::getHost(void) {
	
	return host;
}

int ServerData::getPort() {
	
	return port;
}

std::vector<std::string> ServerData::getServerNames(void) {

	return server_names;
}

int ServerData::getbodySize(void) {
	
	return body_size;
}

std::vector<std::string> ServerData::getMethods(void) {

	return methods;
}

ServerData::~ServerData() {}