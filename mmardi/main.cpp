/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:34:23 by mmardi            #+#    #+#             */
/*   Updated: 2022/11/18 15:21:46 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include "Parser.hpp"
int main(int ac, char **av) {
    if (ac > 2) {
        std::cerr << "Too many arguments\n";
        return 1;
    }
    try
    {
        Parser parser(av);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
  
}