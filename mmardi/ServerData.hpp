/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 23:00:04 by mmardi            #+#    #+#             */
/*   Updated: 2022/11/25 19:11:33 by mmardi           ###   ########.fr       */
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
		int body_size;
		std::vector<std::map<std::string, std::string>> locations;
		std::vector<std::string> methods;
		std::vector<std::string> server_names;
		std::vector<std::string> error_pages;
		std::string index;
		std::string root;
	public:
		ServerData();
		~ServerData();
		void setData(std::map<std::string, std::string> server,  std::vector<std::map<std::string, std::string>> _locations);
		int getPort(void);
		std::string getHost(void);
		std::string getRoot(void);
		std::string getIndex(void);
		void setBodySize(int _n);
		std::vector<std::string> getServerNames(void);
		int getbodySize(void);
		std::vector<std::string> getMethods(void);
		std::vector<std::map<std::string, std::string>> getLocations(void);
};


#endif