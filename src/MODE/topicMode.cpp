/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topicMode.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:50:41 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/08 15:20:23 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void	Server::topicSetRemove(std::map<int, User>::iterator user, std::string buff, std::string channelName) {
	
	std::map<std::string, Channel>::iterator itChan;
	std::map<int, User>::iterator itUser;
	
	size_t pos;
	std::string mode;
	std::string answer;
	std::string nickname;
	
	mode = "MODE #" + channelName + " -t set ";
	pos = buff.find(mode);
	if (pos != std::string::npos)
	{
		nickname = buff.substr(mode.length(), buff.length());
		itChan = findChannelIterator(channelName);
		if (itChan->second.findUser(nickname) == false)
		{
			answer = nickname + " is not in the channel #" + channelName + "\r\n";
			send_out(user->second.getSocket(), answer);
			return ;
		}
		if (itChan->second.findAdminUser(nickname) == false)
		{
			answer = nickname + " is not admin in the channel #" + channelName + "\r\n";
			send_out(user->second.getSocket(), answer);
			return ;
		}
		if (itChan->second.findTopicAdmin(nickname) == true)
		{
			answer = nickname + " already has the rights to the topic #" + channelName + "\r\n";
			send_out(user->second.getSocket(), answer);
			return ;
		}
		itUser = findUserIterator(nickname);
		itChan->second.setTopicAdminOnly(user->second.getSocket(), itUser->second.getSocket(), nickname, channelName);
		return ;
	}
	mode = "MODE #" + channelName + " -t remove ";
	pos = buff.find(mode);
	if (pos != std::string::npos)
	{
		nickname = buff.substr(mode.length(), buff.length());
		itChan = findChannelIterator(channelName);
		if (itChan->second.findUser(nickname) == false)
		{
			answer = nickname + " is not in the channel #" + channelName + "\r\n";
			send_out(user->second.getSocket(), answer);
			return ;
		}
		if (itChan->second.findAdminUser(nickname) == false)
		{
			answer = nickname + " is not admin in the channel #" + channelName + "\r\n";
			send_out(user->second.getSocket(), answer);
			return ;
		}
		if (itChan->second.findTopicAdmin(nickname) == false)
		{
			answer = nickname + " no longer has the right to the topic #" + channelName + "\r\n";
			send_out(user->second.getSocket(), answer);
			return ;
		}
		itUser = findUserIterator(nickname);
		itChan->second.deleteTopicAdmin(user->second.getSocket(), itUser->second.getSocket(), nickname, channelName);
		return ;
	}
	answer = "Usage: MODE <#channel> -t <set/remove> <nickname>\r\n";
	send_out(user->second.getSocket(), answer);
}