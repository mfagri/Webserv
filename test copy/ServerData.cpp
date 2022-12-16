/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 23:00:22 by mmardi            #+#    #+#             */
/*   Updated: 2022/12/16 19:06:24 by mmardi           ###   ########.fr       */
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
	// puts("__________________server:___________________");
	locations = _locations;
	char s[3] = {' ', '\t', '\0'};
	if (server.count("listen") > 0) 
	{
		std::string p = strtok((char *)server.at("listen").c_str(), s);
		if (!this->checkAllNum(p))
		{
			std::cerr << "Ports can take only digits\n";
			exit (1);
		}
		port = std::stoi(p);
	}
	if (server.count("host") > 0) 
	{
		std::string p = strtok((char *)server.at("host").c_str(), s);
		host = p;
	}
	if (server.count("server_name") > 0) 
	{
		std::string names = server.at("server_name");
		char *name = strtok((char *)names.c_str(), s);
		while (name)
		{
			server_names.push_back(name);
			name = strtok(NULL, s);
		}
	}
	if (server.count("body_size") > 0) 
	{
			std::string num = strtok((char *)server.at("body_size").c_str(), s);;
			if (!checkAllNum(num))
			{
				std::cerr << "body_size can take only digits\n" << '\n';
				exit (1);
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
				std::cerr << "ERROR: invalid allowed method \"" + methods[i] + "\"\n" ;
				exit (1);
			}
		}
		
	}
	else {
		std::cerr << "ERROR: missing allowed methods in a sever\n";
		exit (1);
	}
	if (server.count("root") > 0) 
	{
		root = strtok((char *)server.at("root").c_str(), s);
		if (!opendir(root.c_str())) {
			std::cerr << "ERROR: can't access to root path\n";
			exit (1);
		}
	}
	else 
	{
		std::cerr << "ERROR: missing root in server\n";
		exit(1);
	}
	if (server.count("index")) 
	{
		index = strtok((char *)server.at("index").c_str(), s);
	}
	if (server.count("error_pages") > 0) 
	{
		error_pages = strtok((char *)server.at("error_pages").c_str(), s);
	}
	
	for (size_t i = 0; i < locations.size(); i++)
	{
		if (locations[i].count("root"))
		{
			if (!opendir(locations[i].at("root").c_str()))
			{
				std::cerr << "ERROR: can't access to root path in location\n";
				exit(1);
			}
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
					std::cerr << "ERROR: invalide method " <<  p << std::endl;
					exit (1);
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