/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modeRemove.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:05:34 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/07 20:49:28 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"

/*
** --------------------------------- MODE REMOVE ----------------------------------
*/

void	Channel::removeInviteOnly(int socketUser, std::string user, std::string channelName) {

	std::string answer;
	
	if (findUser(user) == false)
	{
		answer = "You have not join the channel #" + channelName + "\r\n";
		send_out(socketUser, answer);
		return ;
	}
	if (findAdminUser(user) == false)
	{
		answer = "You are not admin in channel: #" + channelName + "\r\n";
		send_out(socketUser, answer);
		return ;
	}
	
	answer = "Mode invite only are remove !\r\n";
	send_out(socketUser, answer);
	inviteOnly = false;
}

void	Channel::removePassWord(int socketUser, std::string user, std::string channelName) {

	std::string answer;
	
	if (findUser(user) == false)
	{
		answer = "You have not join the channel #" + channelName + "\r\n";
		send_out(socketUser, answer);
		return ;
	}
	if (findAdminUser(user) == false)
	{
		answer = "You are not admin in channel: #" + channelName + "\r\n";
		send_out(socketUser, answer);
		return ;
	}
	
	answer = "Password are remove !\r\n";
	send_out(socketUser, answer);
	addPassword("");
	passwordSet = false;
}

void	Channel::removeMaxUser(int socketUser, std::string user, std::string channelName) {

	std::string answer;

	if (findUser(user) == false)
	{
		answer = "You have not join the channel #" + channelName + "\r\n";
		send_out(socketUser, answer);
		return ;
	}
	if (findAdminUser(user) == false)
	{
		answer = "You are not admin in channel: #" + channelName + "\r\n";
		send_out(socketUser, answer);
		return ;
	}
	answer = "There are no more capacity limits\r\n";
	send_out(socketUser, answer);
	maxUserSet = false;
	this->_maxUser = 0;
}

bool	Channel::removeAdmin(int socketAdmin, int socketKick, std::string admin) {

	std::string answer;
	std::vector<std::string>::iterator itAdmin = _adminUser.begin();
	std::vector<std::string>::iterator itTopic = _topicAdmin.begin();
	
	while (itAdmin != _adminUser.end())
	{
		if (*itAdmin == admin)
		{
			while (itTopic != _topicAdmin.end())
			{
				if (*itTopic == admin)
				{
					_topicAdmin.erase(itTopic);
					break;
				}
				itTopic++;
			}
			_adminUser.erase(itAdmin);
			answer = admin + " is no longer an admin\r\n";
			send_out(socketAdmin, answer);
			answer = "you are no longer an admin\r\n";
			send_out(socketKick, answer);
			return (true);
		}
		itAdmin++;
	}
	answer = admin + " does not exist in channel\r\n";
	send_out(socketAdmin, answer);
	return (false);
}

/* ************************************************************************** */