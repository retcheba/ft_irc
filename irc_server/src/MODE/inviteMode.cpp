/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:50:13 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/07 16:50:30 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void	Server::inviteSetRemove(std::map<int, User>::iterator user, std::string buff, std::string channelName) {
	
	std::map<std::string, Channel>::iterator itChan;
	
	size_t pos;
	std::string mode;
	std::string answer;
	
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
	answer = "Usage: MODE <#channel> -i <set/remove>\r\n";
	send_out(user->second.getSocket(), answer);
}