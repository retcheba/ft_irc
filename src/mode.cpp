/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:22:55 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/06 15:19:15 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

void	Server::mode(std::map<int, User>::iterator user, std::string buff) {
	
	size_t pos;
	std::string answer;
	std::string channelName = cleanString(buff, "MODE #");

	if (checkAlreadyChannel(channelName) == false)
	{
		answer = "channel has not been created\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	pos = buff.find(" -i ");
	if (pos != std::string::npos)
	{
		return ;
	}
	pos = buff.find(" -t ");
	if (pos != std::string::npos)
	{
		return ;
	}
	pos = buff.find(" -k ");
	if (pos != std::string::npos)
	{
		return ;
	}
	pos = buff.find(" -o ");
	if (pos != std::string::npos)
	{
		return ;
	}
	pos = buff.find(" -l ");
	if (pos != std::string::npos)
	{
		return ;
	}
}

// std::string 	cleanPassword(std::string buff, int length)
// {
// 	std::string clean;
	
// 	while (buff[pos] != ' ' && buff[pos] != '\0' && ( buff[pos] > 32 && buff[pos] < 127))
// 		pos++;
// 	pos++;
// 	start = pos;
// 	while (buff[pos] != ' ' && buff[pos] != '\0' && ( buff[pos] > 32 && buff[pos] < 127))
// 		pos++;
// 	clean = buff.substr(start, pos);
// 	return (clean);
// }

void	Server::inviteSetRemove(std::map<int, User>::iterator user, std::string buff, std::string channelName) {
	
	std::map<std::string, Channel>::iterator itChan;
	
	size_t pos;
	std::string mode;
	
	mode = "MODE #" + channelName + " -i set";
	pos = buff.find(mode);
	if (pos != std::string::npos)
	{
		itChan = findChannelIterator(channelName);
		itChan->second.setInviteOnly(user->second.getSocket(), user->second.getNick(), channelName);
		return ;
	}
	mode = "MODE #" + channelName + " -i remove";
	pos = buff.find(" -i remove");
	if (pos != std::string::npos)
	{
		itChan = findChannelIterator(channelName);
		itChan->second.removeInviteOnly(user->second.getSocket(), user->second.getNick(), channelName);
		return ;
	}
}

void	Server::topicSetRemove(std::map<int, User>::iterator user, std::string buff, std::string channelName) {
	
	std::map<std::string, Channel>::iterator itChan;
	
	size_t pos;
	std::string mode;
	
	mode = "MODE #" + channelName + " -t set";
	pos = buff.find(mode);
	if (pos != std::string::npos)
	{
		itChan = findChannelIterator(channelName);
		itChan->second.setTopicAdminOnly(user->second.getSocket(), user->second.getNick(), channelName);
		return ;
	}
	mode = "MODE #" + channelName + " -t remove";
	pos = buff.find(" -i remove");
	if (pos != std::string::npos)
	{
		itChan = findChannelIterator(channelName);
		itChan->second.removeTopicAdminOnly(user->second.getSocket(), user->second.getNick(), channelName);
		return ;
	}
}

void	Server::passwordSetRemove(std::map<int, User>::iterator user, std::string buff, std::string channelName) {

	std::map<std::string, Channel>::iterator itChan;
	
	size_t pos;
	std::string mode;
	std::string password;
	
	mode = "MODE #" + channelName + " -k set ";
	pos = buff.find(mode);
	if (pos != std::string::npos)
	{
		password = mode.erase(0, mode.length());
		itChan = findChannelIterator(channelName);
		itChan->second.setPassWord(user->second.getSocket(), user->second.getNick(), channelName);
		return ;
	}
	mode = "MODE #" + channelName + " -k remove ";
	pos = buff.find(" -i remove");
	if (pos != std::string::npos)
	{
		password = mode.erase(0, mode.length());
		itChan = findChannelIterator(channelName);
		itChan->second.removePassWord(user->second.getSocket(), user->second.getNick(), channelName);
		return ;
	}	
}

void	Server::operatorGiveTake(std::map<int, User>::iterator user, std::string buff, std::string channelName) {
	
}

void	Server::limitSetRemove(std::map<int, User>::iterator user, std::string buff, std::string channelName) {
	
}
