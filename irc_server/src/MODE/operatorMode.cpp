/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operatorMode.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:53:29 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/08 15:19:57 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void	Server::operatorGiveTake(std::map<int, User>::iterator user, std::string buff, std::string channelName) {
	
	std::map<std::string, Channel>::iterator itChan;
	std::map<int, User>::iterator itUser;
	
	size_t pos;
	std::string mode;
	std::string answer;
	std::string nickname;
	
	mode = "MODE #" + channelName + " -o give ";
	pos = buff.find(mode);
	if (pos != std::string::npos)
	{
		nickname = buff.substr(mode.length(), buff.length());
		itChan = findChannelIterator(channelName);
		if (itChan->second.findUser(nickname) == false)
		{
			answer = nickname + " is not in the channel: #" + channelName + "\r\n";
			send_out(user->second.getSocket(), answer);
			return ;
		}
		itUser = findUserIterator(nickname);
		itChan->second.setAdmin(user->second.getSocket(), itUser->second.getSocket(), nickname);
		return ;
	}
	mode = "MODE #" + channelName + " -o take ";
	pos = buff.find(mode);
	if (pos != std::string::npos)
	{
		nickname = buff.substr(mode.length(), buff.length());
		itChan = findChannelIterator(channelName);
		if (itChan->second.findUser(nickname) == false)
		{
			answer = nickname + " is not in the channel: #" + channelName + "\r\n";
			send_out(user->second.getSocket(), answer);
			return ;
		}
		itUser = findUserIterator(nickname);
		itChan->second.removeAdmin(user->second.getSocket(), itUser->second.getSocket(), nickname);
		return ;
	}
	answer = "Usage: MODE <#channel> -o <give/take> <nickname>\r\n";
	send_out(user->second.getSocket(), answer);
}