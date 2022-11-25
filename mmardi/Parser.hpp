/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:14:28 by mmardi            #+#    #+#             */
/*   Updated: 2022/11/25 19:11:22 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include "ServerData.hpp"
# include <iostream>
# include <fstream>
# include <map>
# include <vector>
# include <iterator>
# include <string>
# include <string.h>

class Parser { 
    private:
        std::string path;
        std::vector<std::string> lines;
        std::vector<std::map<std::string, std::string> > servers;
        std::vector<std::vector<std::map<std::string, std::string>>> serversLocation;
        void readFile();
        void check_conf();
        std::string trimS(std::string str);
        void parsElements();
    public:
        Parser();
        Parser(char **av);
        std::string getElementByServer(unsigned int index, std::string _name);
        std::vector<ServerData> getServers();
        ~Parser();
        class NoValueFound : public std::exception {
            const char *what(void) const throw(){
                return "No value found for element";
            }
        };
        size_t getNumberOfservers();
        class NoSeverfound : public std::exception {
            const char *what(void) const throw(){
                return "No Server found";
            }
        };
        class MissingSemicolon : public std::exception {
            const char *what(void) const throw(){
                return "Messing semicolon at the and of the line";
            }
        };
        class MissingBrackets : public std::exception {
            const char *what(void) const throw(){
                return "Messing brackets for openin or closing a server";
            }
        };
};

#endif
