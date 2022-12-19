/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:33:32 by mmardi            #+#    #+#             */
/*   Updated: 2022/12/19 19:54:46 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_info.hpp"

Parser::Parser() {
    
}
        
Parser::Parser(char **av) 
{
    if (av[1])
        this->path = av[1];
    else
        this->path = "./webserv.conf";
    this->readFile();
    this->parsElements();
}

void Parser::readFile() 
{
    
    std::ifstream confFile(path.c_str());
    std::string element;
    
    if (confFile) 
    {
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

std::string Parser::trimS(std::string str) 
{
    
    for (int i = 0; str[i]; i++) 
    {
        if (str[i] == '\t' || str[i] == ' '  || str[i] == '\n') 
        {
           str.erase(i, 1);
           i = -1;
        }
        else
        {
            break ;
        }
    }
    return (str);
}

bool Parser::checkServer(std::string line) 
{
    int i = 6;
    int bn = 0;
    while(line[0] && (line[0] == ' ' || line[0] == '\t'))
            line.erase(0,1);
    if (strncmp(line.c_str(), "server", 6) == 0) 
    {
        while(line[i]) 
        {
            if (line[i] == '{')
                bn++;
             else if (line[i] != ' ' && line[i] != '\t')
                return false;
            i++;
        }
        if (bn > 1)
            return false;
        return true;
    }
    return false;
}

void Parser::checkElementLocation(std::string key) {

    std::string arr[6] = {"index", "methods", "autoindex", "root", "return","cgi_bin"};
    long unsigned int i = 0;
    while (i < 6 && arr[i] != key)
    {
        i++;
    }
    if (i == 6)
    {
        std::string e = "ERROR: undefined location element name \"" + key + "\"";
        throw std::runtime_error(e);
    }
}

    bool Parser::checkBrackets(std::string s1, std::string s2, char c)
{
    if (strchr(s1.c_str(), c) && strchr(s2.c_str(), c)) 
        return false;
    else if(!strchr(s1.c_str(), c) && !strchr(s2.c_str(), c))
        return false;
    if (strchr(s2.c_str(), c)) {
        int bn = 0;
        for (size_t i = 0; i < s2.length(); i++) 
        {
            if (bn == 1) {
                if (s2[i] != ' ' && s2[i] != '\t')
                    return false;
            }
            if (s2[i] == '{')
                bn++;
        }
    }
    if (strchr(s1.c_str(), c)) {
        int bn = 0;
        for (size_t i = 0; i < s1.length(); i++) 
        {
            if (s1[i] == '{')
                bn++;
            else if (s1[i] != ' ' && s1[i] != '\t')
                return false;
        }
        if (bn > 1)
            return false;
    }
    return true;
}

std::string Parser::getLocationPath(std::string line) 
{
    // std::cout << line <<std::endl; 
    line.erase(0, 8);
    while(line[0] && (line[0] == ' '  || line[0] == '\t'))
        line.erase(0, 1);
    int i = line.length() - 1;
    while (0 <= i && (line[i] == ' ' || line[i] == '\t'  || line[i] == '{'))
    {
        line.erase(i, 1);
        i--;
    }    
    return line;
}

bool    Parser::checkSemicolon(std::string line) 
{
    int i = line.length() - 1;
    while(0 <= i && (line[i] == ' ' || line[i] == '\t')) 
    {
        line.erase(i, 1);
        i--;
    }
    if (line[i] != ';')
        return false;
    int n = 0;
    while(0 <= i) 
    {
        if (line[i] == ';')
            n++; 
        i--;
    }
    if (n > 1)
        return false;
    return true;
}

void Parser::checkElement(std::string key) {

    std::string arr[7] = {"listen", "host", "server_names", "error_pages", "methods", "root", "body_size"};
    long unsigned int i = 0;
    while (i < 7 && arr[i] != key) {
        i++;
    }
    if (i == 7) {
        std::string e = "ERROR: undefined element name \"" + key + "\"";
        throw std::runtime_error(e);
    }
    
}

void Parser::parsElements() 
{
    std::map<std::string, std::string> element;
    std::vector<std::map<std::string, std::string> > locations;
    
    for (size_t i = 0; i < lines.size(); i++) 
    {
        if (checkServer(lines[i])) 
        {
            i++;
            if (!checkBrackets(lines[i], lines[i - 1], '{'))
                throw std::runtime_error("Messing brackets for openin or closing a server");
            if (lines[i][0] == '{')
                        i++;
            while(lines[i][0] != '}') {
                if (strncmp(lines[i].c_str(), "location", 8) == 0) 
                {
                    i++;
                    if (!checkBrackets(lines[i], lines[i - 1], '{')) 
                        throw std::runtime_error("ERROR: messing brackets for openin or closing a server");
                    std::map<std::string, std::string> lElements;
                    std::string path = getLocationPath(lines[i - 1]);
                    if (path.empty())
                        throw std::runtime_error("ERROR: messing location path");
                    lElements.insert(std::pair<std::string, std::string>("location-path", path));
                    if (lines[i][0] == '{')
                        i++;
                    while(lines[i][0] != '}') 
                    {
                        if (lines[i][0] != '}' && (strncmp(lines[i].c_str(), "server", 6) == 0 || strncmp(lines[i].c_str(), "location", 8) == 0 || lines[i] == "The End"))
                            throw std::runtime_error("ERROR: messing brackets for opening or closing a location");
                        if (!checkSemicolon(lines[i]))
                            throw std::runtime_error("ERROR: messing semicolon at the end of the line");
                        char s[4] = {' ', '\t', ';', '\0'};
                        char *key = strtok((char *)lines[i].c_str(), s);
                        checkElementLocation(key);
                        char *value = strtok(NULL, ";");
                         if (!value)
                             throw std::runtime_error("ERROR: no value found for element");
                        lElements.insert(std::pair<std::string, std::string>(key,value));
                        i++;
                    }
                    locations.push_back(lElements);
                    lElements.clear();
                    if (lines[i + 1][0] == '}' && lines[i].length() == 1)
                        break;
                }
                else 
                {
                    if (lines[i][0] != '}' && (strncmp(lines[i].c_str(), "server ", 7) == 0 || lines[i] == "The End"))
                        throw std::runtime_error("ERROR: messing brackets for openin or closing a server");
                    if (!checkSemicolon(lines[i])) 
                            throw std::runtime_error("ERROR: missing semicolon");
                    char s[4] = {' ', '\t', ';', '\0'};
                    char *key = strtok((char *)lines[i].c_str(), s);
                    checkElement(key);
                    char *value = strtok(NULL, ";");
                    if (!value)
                        throw std::runtime_error("ERROR: no value found for element");
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
    if(servers.size() == 0) 
    {
        throw std::runtime_error("ERROR: no server found");
    }
}

std::vector<ServerData> Parser::getServers() 
{
    
    std::vector<ServerData> servs;
    for (size_t i = 0; i < getNumberOfservers(); i++) 
    {
        ServerData s;
        s.setData(servers[i], serversLocation[i]);
        servs.push_back(s);
    }
    for(size_t i = 0;i < servs.size(); i++)
    {
        for (size_t j = i + 1; j < servs.size(); j++)
        {
           if (servs[i].getPort() == servs[j].getPort()) {
                throw std::runtime_error("ERROR: multiple servers with same port");
           }
        }
        
    }
    return servs;
}

size_t Parser::getNumberOfservers() 
{
    
    return servers.size();
}

Parser::~Parser() {
    
}