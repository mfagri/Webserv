/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 23:00:04 by mmardi            #+#    #+#             */
/*   Updated: 2022/11/21 17:44:55 by mmardi           ###   ########.fr       */
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
		std::vector<std::string> methods;
		std::vector<std::string> server_names;
		std::vector<std::string> error_pages;
	public:
		ServerData();
		~ServerData();
		void setData(std::map<std::string, std::string> server);
		int getPort(void);
		std::string getHost(void);
		std::vector<std::string> getServerNames(void);
		int getbodySize(void);
		std::vector<std::string> getMethods(void);	
};


#endif