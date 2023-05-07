/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   passwordMode.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:51:48 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/07 16:52:12 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

bool 	Server::checkPassword(std::string buff)
{
	int i = 0;
	
	if (buff[0] == '\0')
		return (false);
	for (int l = 0; buff[l] != '\0'; l++)
	{
		if (buff[l] == ' ')
			return (false);
	}
	while (buff[i] != ' ' && buff[i] != '\0' && ( buff[i] > 32 && buff[i] < 127))
		i++;
	if (buff[i] != '\0')
		return (false);
	return (true);
}

void	Server::passwordSetRemove(std::map<int, User>::iterator user, std::string buff, std::string channelName) {

	std::map<std::string, Channel>::iterator itChan;
	
	size_t pos;
	std::string mode;
	std::string answer;
	std::string password;
	
	mode = "MODE #" + channelName + " -k set ";
	pos = buff.find(mode);
	if (pos != std::string::npos)
	{
		password = buff.substr(mode.length(), buff.length());
		if (checkPassword(password) == false)
		{
			answer = "Usage: MODE <#channel> -k set <password>\r\n";
			send_out(user->second.getSocket(), answer);
			return;
		}
		itChan = findChannelIterator(channelName);
		itChan->second.setPassWord(user->second.getSocket(), user->second.getNick(), channelName, password);
		return ;
	}
	mode = "MODE #" + channelName + " -k remove";
	pos = buff.find(mode);
	if (pos != std::string::npos)
	{
		itChan = findChannelIterator(channelName);
		itChan->second.removePassWord(user->second.getSocket(), user->second.getNick(), channelName);
		return ;
	}
	answer = "Usage: MODE <#channel> -k <set> <password>\r\n";
	send_out(user->second.getSocket(), answer);
	answer = "Usage: MODE <#channel> -k <remove>\r\n";
	send_out(user->second.getSocket(), answer);
}