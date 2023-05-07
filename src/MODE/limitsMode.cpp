/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limitsMode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:54:09 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/07 16:54:38 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

bool	checkLimitNb(std::string buff) {
	
	char *p;
	double nb;

	nb = strtod(buff.c_str(), &p);
	if (p[0] != '\0')
		return (false);
	if (nb <= 0)
		return (false);
	return (true);
}

void	Server::limitSetRemove(std::map<int, User>::iterator user, std::string buff, std::string channelName) {
	
	std::map<std::string, Channel>::iterator itChan;
	
	char *p;
	size_t pos;
	std::string mode;
	std::string answer;
	std::string number;
	
	mode = "MODE #" + channelName + " -l set ";
	pos = buff.find(mode);
	if (pos != std::string::npos)
	{
		number = buff.substr(mode.length(), buff.length());
		if (checkLimitNb(number) == false)
		{
			answer = "Usage: MODE <#channel> -l set <number>\nNumber must be superior than zero\r\n";
			send_out(user->second.getSocket(), answer);
			return;
		}
		itChan = findChannelIterator(channelName);
		itChan->second.setMaxUser(user->second.getSocket(), user->second.getNick(), channelName, strtod(number.c_str(), &p));
		return ;
	}
	mode = "MODE #" + channelName + " -l remove";
	pos = buff.find(mode);
	if (pos != std::string::npos)
	{
		itChan = findChannelIterator(channelName);
		itChan->second.removeMaxUser(user->second.getSocket(), user->second.getNick(), channelName);
		return ;
	}
	answer = "Usage: MODE <#channel> -l <set> <number>\r\n";
	send_out(user->second.getSocket(), answer);
	answer = "Usage: MODE <#channel> -l <remove>\r\n";
	send_out(user->second.getSocket(), answer);
}