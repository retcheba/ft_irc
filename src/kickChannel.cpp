/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kickChannel.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:29:55 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/05 14:56:33 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

void	Server::kickChannel(std::map<int, User>::iterator user, std::string buff) {
	
	std::string answer;
	std::string userName;
	std::string channelName;
	
	if (!checkFormatMessage(buff, "KICK #", 7))
	{
		answer = "Usage: KICK <#channel> <nickname>\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	channelName = cleanStringCmd(buff, "KICK #");
	if (checkAlreadyChannel(channelName) == false)
	{
		answer = "channel has not been created\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	if (user->second.findChannel(channelName) == false)
	{
		answer = "You have not join the channel " + channelName + "\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	if (user->second.checkAdminChannel(channelName) == false)
	{
		answer = "You are not admin in channel: " + channelName + "\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	userName = buff.substr(( 6 + channelName.length() + 1 ), buff.length());
	if (user->second.getNick() == userName)
	{
		answer = "Impossible to kick because, you are admin in channel: " + channelName + "\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	std::map<int, User>::iterator it = this->_clients.begin();
	while (it != this->_clients.end())
	{
		if (it->second.getNick() == userName)
		{
			if (it->second.checkAdminChannel(channelName) == true && it->second.findChannel(channelName) == true)
			{
				answer = "Impossible to kick because, " + userName + " is admin in channel #" + channelName + "\r\n";
				send_out(user->second.getSocket(), answer);
				return;
			}
			it->second.deleteChannel(channelName);
			answer = "You have been KICK\r\n";
			send_out(it->second.getSocket(), answer);
			answer = "You have KICK " + userName + "\r\n";
			send_out(user->second.getSocket(), answer);
			return;
		}
		it++;
	}
	answer = userName + " not exist in channel #" + channelName + "\r\n";
	send_out(user->second.getSocket(), answer);
	return;
}