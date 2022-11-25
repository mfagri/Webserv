/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 18:53:17 by mfagri            #+#    #+#             */
/*   Updated: 2022/11/25 18:57:44 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include "request.hpp"
class Request;

class Response{
    private:
        std::string uri;
        std::string res;
        int status;
    public:
        Response();
        Response(Request &req);
};
#endif