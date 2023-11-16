/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channelMessage.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:17:31 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/07 16:47:00 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void	Server::sendMessageChannel(std::map<int, User>::iterator user, std::string buff) {	

	std::map<std::string, Channel>::iterator itChan;
			
	std::string answer;
	std::string message;
	std::string channelName;
	size_t pos;	
	
	if (( pos = _buff.find("SEND #") ) != 0 )
	{
		answer = "Usage: SEND <#channel> <message>\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	if (!checkFormatMessage(buff, "SEND #", 6))
	{
		answer = "Usage: SEND <#channel> <message>\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	channelName = cleanStringCmd(buff, "SEND #");
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

	std::map<int, User>::iterator it = this->_clients.begin();
	while (it != this->_clients.end())
	{
		if (itChan->second.findUser(it->second.getNick()) == true)
		{
			message = buff.substr(( strlen("SEND #") + channelName.length() + 1 ), buff.length());
			answer = "#" + channelName + " " + user->second.getNick() + ": " + message + "\r\n"; 
			send_out(it->second.getSocket(), answer);
		}
		it++;
	}
}
