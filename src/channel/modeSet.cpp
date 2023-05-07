/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modeSet.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:04:04 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/07 16:05:57 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"

/*
** --------------------------------- MODE SET ----------------------------------
*/

void	Channel::setInviteOnly(int socketUser, std::string user, std::string channelName) {

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
	
	answer = "Mode invite only are set !\r\n";
	send_out(socketUser, answer);
	inviteOnly = true;
}

void	Channel::setTopicAdminOnly(int socketAdminTopic, int socketNewAdminTopic, std::string user, std::string channelName) {

	std::string answer;

	if (findUser(user) == false)
	{
		answer = "You have not join the channel #" + channelName + "\r\n";
		send_out(socketAdminTopic, answer);
		return ;
	}
	if (findAdminUser(user) == false)
	{
		answer = "You are not admin in channel: #" + channelName + "\r\n";
		send_out(socketAdminTopic, answer);
		return ;
	}
	_topicAdmin.push_back(user);
	answer = user + " can change the channel topic now\r\n";
	send_out(socketAdminTopic, answer);
	answer = "You can change the topic in the channel #" + channelName + "\r\n";
	send_out(socketNewAdminTopic, answer);
}

void	Channel::setPassWord(int socketUser, std::string user, std::string channelName, std::string password) {

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
	
	answer = "Password are set !\r\n";
	send_out(socketUser, answer);
	addPassword(password);
	passwordSet = true;
}

void	Channel::setMaxUser(int socketUser, std::string user, std::string channelName, double maxUSer) {
	
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
	answer = "Max user are change\r\n";
	send_out(socketUser, answer);
	maxUserSet = true;
	this->_maxUser = maxUSer;
}

bool	Channel::setAdmin(int socketAdmin, int socketNewAdmin, std::string admin) {
	
	std::string answer;
	std::vector<std::string>::iterator itAcces = _accesUser.begin();
	std::vector<std::string>::iterator itAdmin = _adminUser.begin();

	while (itAcces != _accesUser.end())
	{
		if (*itAcces == admin)
		{
			while (itAdmin != _adminUser.end())
			{
				if (*itAdmin == admin)
				{
					answer = admin + " is already an admin\r\n";
					send_out(socketAdmin, answer);
					return (false);
				}
				itAdmin++;
			}
			_adminUser.push_back(admin);
			_topicAdmin.push_back(admin);
			answer = admin + " is an admin\r\n";
			send_out(socketAdmin, answer);
			answer = "you are an admin\r\n";
			send_out(socketNewAdmin, answer);
			return (true);
		}
		itAcces++;
	}
	answer = admin + " does not exist in channel\r\n";
	send_out(socketAdmin, answer);
	return (false);
}

/* ************************************************************************** */