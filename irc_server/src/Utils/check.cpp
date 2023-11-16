/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:45:00 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/08 16:14:16 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

bool 	Server::checkAlreadyChannel(std::string buff) {
	
	std::map<std::string, Channel>::iterator it = _channel.begin();
	
	while (it != _channel.end())
	{
		if (it->first == buff)
			return (true);
		it++;
	}
	return (false);
}

bool 	Server::checkAlreadyUser(std::string buff) {
	
	std::map<int, User>::iterator it = _clients.begin();
	
	while (it != _clients.end())
	{
		if (it->second.getNick() == buff)
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

bool 	Server::checkLastMessage(std::string buff, std::string cmd)
{
	size_t pos;

	pos = buff.find(cmd);
	if (pos == std::string::npos)
		return (false);
	while (buff[pos] != ' ' && buff[pos] != '\0' && ( buff[pos] > 32 && buff[pos] < 127))
		pos++;
	if (buff[pos] != ' ')
		return (false);
	if (buff[pos + 1] == '\0')
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