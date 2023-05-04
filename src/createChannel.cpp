/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createChannel.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:53:04 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/04 18:29:47 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

static int 	checkFormatJoin(std::string buff)
{
	int i = 5;
	size_t pos;
	std::string user;

	pos = buff.find("JOIN #");
	if (pos == std::string::npos || pos != 0)
		return (0);
	while (buff[i] != ' ' && buff[i] != '\0' && ( buff[i] > 32 && buff[i] < 127))
		i++;
	if (buff[i] != '\0')
		return (0);
	return (1);
}

int 	Server::checkAlreadyChannel(std::string buff)
{	
	std::map<int, std::string>::iterator channel = _channel.begin();
	
	while (channel != _channel.end())
	{
		if (channel->second == buff)
			return (true);
		channel++;
	}
	return (false);
}

void		Server::createChannel(std::map<int, User>::iterator user, std::string buff) {
	
	std::string channelName = cleanString(buff, "JOIN #");
	std::string answer;
	
	if (!checkFormatJoin(buff))
	{
		if (send(user->second.getSocket(), "Usage: JOIN <#channel>\n", 24, 0) == -1)
			std::cerr << "Error: Message can't be sent" << std::endl;
		return;
	}
	if (checkAlreadyChannel(channelName) == true)
	{
		if (user->second.findChannel(channelName) == true)
		{
			answer = "You are already in channel <" + channelName + ">\n";
			if (send(user->second.getSocket(), answer.c_str(), answer.length(), 0) == -1)
				std::cerr << "Error: Message can't be sent" << std::endl;
			return;
		}
		user->second.setChan(channelName, false);
		answer = "You have join channel <" + channelName + ">\n";
		if (send(user->second.getSocket(), answer.c_str(), answer.length(), 0) == -1)
			std::cerr << "Error: Message can't be sent" << std::endl;
		return;
	}

	_channel.insert(std::pair<int, std::string>(user->second.getSocket(), channelName));
	user->second.setChan(channelName, true);
	answer = "Channel: <" + channelName + "> has been create\n";
	
	if (send(user->second.getSocket(), answer.c_str(), answer.length(), 0) == -1)
		std::cerr << "Error: Message can't be sent" << std::endl;
	return;
}
