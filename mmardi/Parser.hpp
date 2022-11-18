/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:14:28 by mmardi            #+#    #+#             */
/*   Updated: 2022/11/18 16:08:03 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <iostream>
# include <fstream>

class Parser {
    private:
        std::string path;
    public:
        Parser();
        Parser(char **av);
        void readFile();
        ~Parser();
};

#endif
