/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:14:28 by mmardi            #+#    #+#             */
/*   Updated: 2022/11/24 16:48:45 by mfagri           ###   ########.fr       */
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
};

#endif
