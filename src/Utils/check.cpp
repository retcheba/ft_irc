/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:45:00 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/08 13:12:34 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

int 	Server::checkAlreadyChannel(std::string buff) {
	
	std::map<std::string, Channel>::iterator it = _channel.begin();
	
	while (it != _channel.end())
	{
		if (it->first == buff)
			return (true);
		it++;
	}
	return (false);
}

bool 	Server::checkFormatMessage(std::string buff, std::string remove, int i) {
	
	size_t pos;
	std::string user;

	pos = buff.find(remove);
	if (pos == std::string::npos || pos != 0)
		return (false);
	while (buff[i] != ' ' && buff[i] != '\0' && ( buff[i] > 32 && buff[i] < 127))
		i++;
	if (buff[i] != ' ')
		return (false);
	if (buff[i + 1] == '\0')
		return (false);
	return (true);
}

bool	Server::checkSpace(std::string buff) {
	
	int i = 0;

	while (buff[i] != '\0')
	{
		if (buff[i] == ' ')
			return (false);
		i++;
	}
	return (true);
}