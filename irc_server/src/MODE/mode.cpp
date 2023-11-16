/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:22:55 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/07 16:54:35 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void	Server::mode(std::map<int, User>::iterator user, std::string buff) {
	
	size_t pos;
	std::string answer;
	std::string channelName = cleanStringCmd(buff, "MODE #");

	if (( pos = _buff.find("MODE #") ) != 0 )
	{
		answer = "Usage: MODE <#channel> -i <set/remove>\nUsage: MODE <#channel> -t <set/remove> <nickname>\nUsage: MODE <#channel> -k <set> <password>\nUsage: MODE <#channel> -k <remove>\nUsage: MODE <#channel> -o <give/take> <nickname>\nUsage: MODE <#channel> -l <set> <number>\nUsage: MODE <#channel> -l <remove>\r\n" ;
		send_out(user->second.getSocket(), answer);
		return;
	}
	if (checkAlreadyChannel(channelName) == false)
	{
		answer = "channel has not been created\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	pos = buff.find(" -i ");
	if (pos != std::string::npos)
	{
		inviteSetRemove(user, buff, channelName);
		return ;
	}
	pos = buff.find(" -t ");
	if (pos != std::string::npos)
	{
		topicSetRemove(user, buff, channelName);
		return ;
	}
	pos = buff.find(" -k ");
	if (pos != std::string::npos)
	{
		passwordSetRemove(user, buff, channelName);
		return ;
	}
	pos = buff.find(" -o ");
	if (pos != std::string::npos)
	{
		operatorGiveTake(user, buff, channelName);
		return ;
	}
	pos = buff.find(" -l ");
	if (pos != std::string::npos)
	{
		limitSetRemove(user, buff, channelName);
		return ;
	}
	answer = "Usage: MODE <#channel> -i <set/remove>\nUsage: MODE <#channel> -t <set/remove> <nickname>\nUsage: MODE <#channel> -k <set> <password>\nUsage: MODE <#channel> -k <remove>\nUsage: MODE <#channel> -o <give/take> <nickname>\nUsage: MODE <#channel> -l <set> <number>\nUsage: MODE <#channel> -l <remove>\r\n" ;
	send_out(user->second.getSocket(), answer);
}
