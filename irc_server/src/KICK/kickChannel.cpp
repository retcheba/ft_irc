/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kickChannel.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:29:55 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/08 15:47:50 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void	Server::kickChannel(std::map<int, User>::iterator user, std::string buff) {
	
	std::map<std::string, Channel>::iterator itChan;
	
	std::string answer;
	std::string userName;
	std::string channelName;
	size_t pos;
	
	if (( pos = _buff.find("KICK #") ) != 0 )
	{
		answer = "Usage: KICK <#channel> <nickname>\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
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
	itChan = findChannelIterator(channelName);

	if (itChan->second.findUser(user->second.getNick()) == false)
	{
		answer = "You have not join the channel #" + channelName + "\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
		
	if (itChan->second.findAdminUser(user->second.getNick()) == false)
	{
		answer = "You are not admin in channel: #" + channelName + "\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
		
	userName = buff.substr(( 6 + channelName.length() + 1 ), buff.length());
	std::map<int, User>::iterator it = this->_clients.begin();
	while (it != this->_clients.end())
	{
		if (it->second.getNick() == userName)
		{
			itChan->second.deleteUser(user->second.getSocket(), it->second.getSocket(), userName, channelName);
			if (itChan->second.channelSize() <= 0)
			{
				this->_channel.erase(itChan);
				answer = "The channel #" + channelName + " has been deleted because there is no one left\r\n";
				send_out(user->second.getSocket(), answer);
			}
			return;
		}
		it++;
	}
	answer = userName + " doesn't exist in the channel: #" + channelName + "\r\n";
	send_out(user->second.getSocket(), answer);
	return;
}
