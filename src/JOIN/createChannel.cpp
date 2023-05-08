/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createChannel.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:53:04 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/08 15:01:50 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

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

void		Server::createChannel(std::map<int, User>::iterator user, std::string buff) {
	
	std::map<std::string, Channel>::iterator itChan;
	
	std::string channelName = cleanStringCmd(buff, "JOIN #");
	std::string password;
	std::string answer;
	std::string mode;
	size_t pos;
	
	if (( pos = _buff.find("JOIN") ) != 0 || channelName[0] == '\0')
	{
		answer = "Usage: JOIN <#channel> (password)\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	mode = "JOIN #" + channelName + " ";
	if (mode.length() < buff.length())
		password = buff.substr(mode.length(), buff.length());
	if (!checkFormatJoin(buff) && checkPassword(password) == false)
	{
		answer = "Usage: JOIN <#channel> (password)\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	if (checkAlreadyChannel(channelName) == true)
	{
		itChan = findChannelIterator(channelName);
		
		if (itChan->second.modeMaxUserSet() == true)
		{
			if (itChan->second.channelSize() >= itChan->second.getMaxUser())
			{
				answer = "The capacity of the channel is at its maximum\r\n";
				send_out(user->second.getSocket(), answer);
				return ;
			}
		}
		if (itChan->second.modeInviteOnly() == true)
		{
			answer = "The channel is in mode invite-only\r\n";
			send_out(user->second.getSocket(), answer);
			return ;
		}
		if (itChan->second.modePasswordSet() == true)
		{
			if (itChan->second.getPassword() != password)
			{
				answer = "Wrong password\r\n";
				send_out(user->second.getSocket(), answer);
				return ;
			}
		}
		if (itChan->second.getAccesUser(user->second.getSocket(), channelName) == true)
			return;
			
		itChan->second.addUser(user->second.getSocket(), user->second.getNick(), channelName);
		return;
	}
	if (checkSpace(channelName) == false)
	{
		answer = "Impossible to put SPACE when you create a new channel\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	Channel chan(user->second.getSocket(), user->second.getNick(),channelName);

	this->_channel.insert(std::pair<std::string, Channel>(channelName, chan));
	return;
}