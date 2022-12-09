/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:14:28 by mmardi            #+#    #+#             */
/*   Updated: 2022/12/09 00:08:07 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

#include "general_info.hpp"

class Parser { 
    private:
        std::string path;
        std::vector<std::string> lines;
        std::vector<std::map<std::string, std::string> > servers;
        std::vector<std::vector<std::map<std::string, std::string> > > serversLocation;
        void readFile();
        void check_conf();
        std::string trimS(std::string str);
        void parsElements();
        bool checkLocation(std::string location);
        bool checkServer(std::string line);
        bool checkBrackets(std::string s1, std::string s2, char c);
        std::string getLocationPath(std::string line);
        void checkElement(std::string key);
        void checkElementLocation(std::string key);
        bool checkSemicolon(std::string line);

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
         class MissingLocationBrackets : public std::exception {
            const char *what(void) const throw(){
                return "Messing brackets for openin or closing a location";
            }
        };
};

#endif
