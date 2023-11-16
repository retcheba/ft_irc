/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findIterator.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:43:47 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/07 16:44:21 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

std::map<std::string, Channel>::iterator 	Server::findChannelIterator(std::string channelName)
{	
	std::map<std::string, Channel>::iterator it = _channel.begin();
	
	while (it != _channel.end())
	{
		if (it->first == channelName)
			return (it);
		it++;
	}
	return (it);
}

std::map<int, User>::iterator 	Server::findUserIterator(std::string nickname) {

	std::map<int, User>::iterator it = _clients.begin();
	
	while (it != _clients.end())
	{
		if (it->second.getNick() == nickname)
			return (it);
		it++;
	}
	return (it);
}