/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:33:32 by mmardi            #+#    #+#             */
/*   Updated: 2022/11/18 21:19:35 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Parser.hpp"
# include <vector>
# include <iterator>
# include <string>
Parser::Parser() {}
        
Parser::Parser(char **av) {
    if (av[1])
        this->path = av[1];
    else
        this->path = "./webserv.conf";
    this->readFile();
}

void Parser::readFile() {
    
    std::ifstream confFile(path);
    std::vector<std::string> lines;
    std::string element;
    if (confFile) {
        while(std::getline(confFile, element))
        {
            element = this->trimS(element);
            std::cout << '[' << element << ']'<< std::endl;
            if (element[0]) {
                lines.push_back(element);
            }
        }
    }
    // for (std::vector<std::string>::iterator ptr = lines.begin(); ptr != lines.end(); ptr++)
    //     std::cout << *ptr + "\n";
}

std::string Parser::trimS(std::string str) {
    
    for (int i = 0; str[i]; i++) {
        if (str[i] == '\t' || str[i] == ' '  || str[i] == '\n') {
            if (str[i] == '\t')
                std::cout << "imhere " << i << '\n'; 
            str.erase(i, 1);
        }
        else
            break ;
    }
    return (str);
}

Parser::~Parser(){}