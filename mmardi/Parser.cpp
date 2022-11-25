/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:33:32 by mmardi            #+#    #+#             */
/*   Updated: 2022/11/25 19:10:48 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Parser.hpp"

Parser::Parser() {}
        
Parser::Parser(char **av) {
    if (av[1])
        this->path = av[1];
    else
        this->path = "./webserv.conf";
    this->readFile();
    this->parsElements();
}

void Parser::readFile() {
    
    std::ifstream confFile(path.c_str());
    std::string element;
    if (confFile) {
        while(std::getline(confFile, element))
        {
            element = this->trimS(element);
            if (element[0]) {
                this->lines.push_back(element);
            }
        }
        this->lines.push_back("The End");
    }
}

std::string Parser::trimS(std::string str) {
    
    for (int i = 0; str[i]; i++) {
        if (str[i] == '\t' || str[i] == ' '  || str[i] == '\n') {
           str.erase(i, 1);
           i = -1;
        }
        else{
            break ;
        }
    }
    return (str);
}

void Parser::parsElements() {
    std::map<std::string, std::string> element;
    std::vector<std::map<std::string, std::string>> locations;
    
    for (size_t i = 0; i < lines.size(); i++) {
        if (strncmp(lines[i++].c_str(), "server", 6) == 0) {
            if (lines[i++][0] != '{')
                throw MissingBrackets();
            i++;
            while(lines[i][0] != '}') {
                if (strncmp(lines[i].c_str(), "location", 8) == 0) {
                    std::map<std::string, std::string> lElements;
                    strtok((char *)lines[i].c_str(), " ");
                    char *path = strtok(NULL, " ");
                    if (!path)
                        throw NoValueFound();
                    lElements.insert(std::pair<std::string, std::string>("location-path", path));
                    i++;
                    if (lines[i][0] != '[') {
                        std::cerr << "Missing location brackets\n";
                        exit (1);
                    }
                    i++;
                    while(lines[i][0] != ']') {
                        if (lines[i][lines[i].length() - 1] != ';')
                            throw MissingSemicolon();
                        char *key = strtok((char *)lines[i].c_str(), " ");
                        char *value = strtok(NULL, ";");
                         if (!value)
                             throw NoValueFound();
                        lElements.insert(std::pair<std::string, std::string>(key,value));
                        i++;
                    }
                    locations.push_back(lElements);
                    lElements.clear();
                    if (lines[i][0] == '}' && lines[i].length() == 1)
                        break;
                }
                else {
                    if (lines[i][lines[i].length() - 1] != ';') {
                            throw MissingSemicolon();
                    }
                    if (lines[i][0] != '}' && (strncmp(lines[i +1 ].c_str(), "server ", 7) == 0 || lines[i + 1] == "The End"))
                        throw MissingBrackets();
                    char *key = strtok((char *)lines[i].c_str(), " ");
                    char *value = strtok(NULL, ";");
                    if (!value)
                        throw NoValueFound();
                    element.insert(std::pair<std::string, std::string>(key,value));
                }
                i++;
            }
        servers.push_back(element);
        serversLocation.push_back(locations);
        locations.clear();
        element.clear();
        }
    }
    if(servers.size() == 0) {
        throw NoSeverfound();
    }
}

std::vector<ServerData> Parser::getServers() {
    
    std::vector<ServerData> servs;
    for (size_t i = 0; i < getNumberOfservers(); i++) {
        ServerData s;
        s.setData(servers[i], serversLocation[i]);
        servs.push_back(s);
    }
    return servs;
}


std::string Parser::getElementByServer(unsigned int index, std::string _name) {
    
    if (index >= getNumberOfservers()) {
        std::cerr << "index out of bound a Nour Eddine\n";
        throw NoSeverfound();
    }
    return this->servers[index].at(_name);
}

size_t Parser::getNumberOfservers() {
    
    return servers.size();
}

Parser::~Parser() {}