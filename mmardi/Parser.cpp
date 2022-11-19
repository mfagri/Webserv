/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:33:32 by mmardi            #+#    #+#             */
/*   Updated: 2022/11/19 01:15:26 by mmardi           ###   ########.fr       */
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
    }
    // for (std::vector<std::string>::iterator ptr = this->lines.begin(); ptr != lines.end(); ptr++)
    //     std::cout << *ptr + "\n";
}

std::string Parser::trimS(std::string str) {
    
    for (int i = 0; str[i]; i++) {
        if (str[i] == '\t' || str[i] == ' '  || str[i] == '\n') {
            str.erase(i, 1);
        }
        else
            break ;
    }
    return (str);
}

void Parser::parsElements() {
    std::map<std::string, std::string> element;
    for (size_t i = 0; i < lines.size(); i++) {
        if (strncmp(lines[i].c_str(), "server", 6) == 0) {
            i++;
            if (strncmp(lines[i].c_str(), "listen", 6) == 0) {
                strtok((char *)lines[i].c_str(), " ");
                char *p = strtok(NULL, " ;");
                puts(p);      
            }
        }
    }
}


Parser::~Parser(){}