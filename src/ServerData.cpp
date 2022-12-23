/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 23:00:22 by mmardi            #+#    #+#             */
/*   Updated: 2022/12/23 17:50:15 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_info.hpp"

ServerData::ServerData() {
	port = 80;
	host = "0.0.0.0";
	body_size = 1024;
}

int ServerData::checkAllNum(std::string num)
{
	size_t i = 0;
	while (i < num.length())
	{
		if (!isdigit(num[i]))
			return 0;
		i++;
	}
	return 1;
}

int ServerData::setData(std::map<std::string, std::string> server, std::vector<std::map<std::string, std::string> > _locations) {
	locations = _locations;
	char s[3] = {' ', '\t', '\0'};
	if (server.count("listen") > 0) 
	{
		std::string p = strtok((char *)server.at("listen").c_str(), s);
		if (!this->checkAllNum(p))
		{
			throw std::runtime_error("ERROR: ports must take only degits");
		}
		port = std::stoi(p);
	}
	if (server.count("host") > 0) 
	{
		std::string p = strtok((char *)server.at("host").c_str(), s);
		host = p;
	}
	if (server.count("server_names") > 0) 
	{
		std::string names = server.at("server_names");
		char *name = strtok((char *)names.c_str(), s);
		while (name)
		{
			server_names.push_back(name);
			name = strtok(NULL, s);
		}
	}
	else {
				throw std::runtime_error("ERROR: Missing server_names");
	}
	if (server.count("body_size") > 0) 
	{
			std::string num = strtok((char *)server.at("body_size").c_str(), s);;
			if (!checkAllNum(num))
			{
				throw std::runtime_error("ERROR: body_size must take only digits");
			}
			body_size = std::stoi(num);
	}
	if (server.count("methods") > 0)
	{
		std::string m = server.at("methods");
		char *method = strtok((char *)m.c_str(), "	 ");
		while (method) 
		{
			methods.push_back(method);
			method = strtok(NULL, "	 ");
		}
		for (size_t i = 0; i < methods.size(); i++)
		{
			if (methods[i] != "GET" && methods[i] != "POST" && methods[i] != "DELETE") {
				std::string e = "ERROR: invalid allowed method \"" + methods[i] + "\"";
				throw std::runtime_error(e);
			}
		}
		
	}
	else {
		throw std::runtime_error("ERROR: missing allowed methods in a sever");
	}
	if (server.count("root") > 0) 
	{
		root = strtok((char *)server.at("root").c_str(), s);
		DIR *d = opendir(root.c_str());
		if (!d) {	
			throw std::runtime_error("ERROR: can't access to root path");
		}
		closedir(d);
	}
	else 
	{
		throw std::runtime_error("ERROR: missing root in server");
	}
	if (server.count("index")) 
	{
		index = strtok((char *)server.at("index").c_str(), s);
	}
	if (server.count("error_pages") > 0) 
	{
		error_pages = strtok((char *)server.at("error_pages").c_str(), s);
		DIR* d = opendir(error_pages.c_str());
		if (!d) {
			throw std::runtime_error("ERROR: can't access error_pages path");
		}
		closedir(d);
	}
	else {
		throw std::runtime_error("ERROR: missing error_pages in server");
	}
	for (size_t i = 0; i < locations.size(); i++)
	{
		if (locations[i].count("root"))
		{
			DIR *d = opendir(locations[i].at("root").c_str());
			if (!d)
			{
				throw std::runtime_error("ERROR: can't access to root path in location");
			}
			closedir(d);
		}
		else {
			locations[i].insert(std::pair<std::string, std::string>("root", this->root));
		}
		if (!locations[i].count("methods")) {
			locations[i].insert(std::pair<std::string, std::string>("methods", server.at("methods")));
		}
		else {
			std::string methods = locations[i].at("methods");
			char *p = strtok((char *)methods.c_str(), " 	");
			while (p) {
				if (strcmp(p, "GET") != 0 && strcmp(p, "POST") != 0 && strcmp(p, "DELETE") != 0)
				{
					std::string e = "ERROR: invalide method ";
					e.append(p);
					throw std::runtime_error(e);
				}
				p = strtok(NULL, " 	");
			}
		}
		for (size_t j = 0; j < locations[i].at("methods").size(); j++)
		{
			if (locations[i].at("methods")[j] == '\t') {
				locations[i].at("methods")[j] = ' ';
			}
		}
		
	}
	return 1;
}

std::string ServerData::getHost(void)
 {
	
	return host;
}

int ServerData::getPort()
 {
	
	return port;
}

std::vector<std::string> ServerData::getServerNames(void)
 {

	return server_names;
}

int ServerData::getbodySize(void)
 {
	
	return body_size;
}

std::vector<std::string> ServerData::getMethods(void)
 {

	return methods;
}

std::vector<std::map<std::string, std::string> > ServerData::getLocations(void) {
	
	return locations;
}

std::string ServerData::getRoot() {
	return root;
}

std::string ServerData::getIndex(void) 
{

	return index;
}

std::string ServerData::getErrorPages(void) 
{
	
	return error_pages;
}

ServerData::~ServerData() {}