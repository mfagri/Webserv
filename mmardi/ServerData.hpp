/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 23:00:04 by mmardi            #+#    #+#             */
/*   Updated: 2022/11/21 00:53:20 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERDATA_HPP
# define SERVERDATA_HPP

# include <iostream>
# include <map>
# include <vector>
# include <string.h>
class ServerData {
	private:
		int port;
		std::string host;
		std::vector<std::string> server_names;
		std::vector<std::string> error_pages;
	public:
		ServerData();
		~ServerData();
		void setData(std::map<std::string, std::string> server);
		int getPort(void);
		std::string getHost(void);
		
};


#endif