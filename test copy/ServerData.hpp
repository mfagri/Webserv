/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 23:00:04 by mmardi            #+#    #+#             */
/*   Updated: 2022/11/28 23:59:36 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERDATA_HPP
# define SERVERDATA_HPP

#include "general_info.hpp"

class ServerData {
	private:
		int port;
		std::string host;
		int body_size;
		std::vector<std::map<std::string, std::string> > locations;
		std::vector<std::string> methods;
		std::vector<std::string> server_names;
		std::string error_pages;
		std::string index;
		std::string root;
	public:
		ServerData();
		~ServerData();
		int setData(std::map<std::string, std::string> server,  std::vector<std::map<std::string, std::string> > _locations);
		int getPort(void);
		std::string getHost(void);
		std::string getRoot(void);
		std::string getIndex(void);
		void setBodySize(int _n);
		std::vector<std::string> getServerNames(void);
		int getbodySize(void);
		std::string	getErrorPages(void);
		std::vector<std::string> getMethods(void);
		std::vector<std::map<std::string, std::string> > getLocations(void);
		int checkAllNum(std::string num);
};


#endif