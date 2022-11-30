/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 23:00:22 by mmardi            #+#    #+#             */
/*   Updated: 2022/11/30 16:40:26 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_info.hpp"

ServerData::ServerData() {
	port = 30;
	host = "0.0.0.0";
	body_size = 1024;
}

void ServerData::setData(std::map<std::string, std::string> server, std::vector<std::map<std::string, std::string> > _locations) {
	locations = _locations;
	if (server.count("listen") > 0) {
		std::string p = server.at("listen");
		port = std::stoi(p);
	}
	if (server.count("host") > 0) {
		std::string p = server.at("host");
		host = p;
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
	if (server.count("root") > 0) {
		root = server.at("root");
	}
	else {
		std::cerr << "missing root in server\n";
		exit(1);
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

std::vector<std::map<std::string, std::string> > ServerData::getLocations(void) {
	
	return locations;
}

ServerData::~ServerData() {}