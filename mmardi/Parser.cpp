/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:33:32 by mmardi            #+#    #+#             */
/*   Updated: 2022/11/18 18:45:26 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Parser.hpp"
# include <vector>
# include <iterator>
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
    std::string elements;
    if (confFile) {
        while(std::getline(confFile, elements))
            lines.push_back(elements);
    }
    // for (std::vector<std::string>::iterator ptr = lines.begin(); ptr != lines.end(); ptr++)
    //     std::cout << "|" + *ptr;
}

Parser::~Parser(){}