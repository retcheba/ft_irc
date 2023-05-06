/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:27:37 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/06 17:03:53 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

static bool 	checkFormat(std::string buff, std::string remove, int i)
{
	size_t pos;
	std::string user;

	pos = buff.find(remove);
	if (pos == std::string::npos || pos != 0)
		return (false);
	while (buff[i] != ' ' && buff[i] != '\0' && ( buff[i] > 32 && buff[i] < 127))
		i++;
	if (buff[i] != ' ')
		return (false);
	i++;
	if (buff[i] == '\0')
		return (false);
	while (buff[i] != ' ' && buff[i] != '\0' && ( buff[i] > 32 && buff[i] < 127))
		i++;
	if (buff[i] != '\0')
		return (false);

	return (true);
}

void	Server::invite(std::map<int, User>::iterator user, std::string buff)
{
	std::map<std::string, Channel>::iterator itChan;
	std::string	answer;
	std::string	channelName;
	std::string	nickname;

	if (!checkFormat(buff, "INVITE #", 8))
	{
		answer = "Usage: INVITE <#channel> <nickname>\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	channelName = cleanStringCmd(buff, "INVITE #");
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
	nickname = buff.substr(( strlen("INVITE #") + channelName.length() + 1 ), buff.length());
	if (alreadyNickname(nickname))
	{
		answer = "this user doesn't exist: " + nickname + "\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	if ( itChan->second.findUser(nickname) == true )
	{
		answer = "this user is already in the channel: " + nickname + "\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}

	std::map<int, User>::iterator invited = this->_clients.begin();
	
	while (invited != this->_clients.end())
	{
		if (invited->second.getNick() == nickname)
		{
			itChan->second.addUser( invited->second.getSocket(), invited->second.getNick(), channelName );
			answer = "you have invited " + nickname + " to the channel" + "\r\n";
			send_out(user->second.getSocket(), answer);
			break;
		}
		invited++;
	}

	return;
}
