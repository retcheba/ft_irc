/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:11:00 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/08 19:04:33 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"

/*
** --------------------------------- DELETE ----------------------------------
*/

bool	Channel::deleteUser(int socketUser, int socketNewUser, std::string user, std::string channelName) {

	std::string answer;
	std::vector<std::string>::iterator itAcces = _accesUser.begin();
	std::vector<std::string>::iterator itAdmin = _adminUser.begin();
	std::vector<std::string>::iterator itTopic = _topicAdmin.begin();

	while (itAcces != _accesUser.end())
	{
		if (*itAcces == user)
		{
			while (itAdmin != _adminUser.end())
			{
				if (*itAdmin == user)
				{
					while (itTopic != _topicAdmin.end())
					{
						if (*itTopic == user)
						{
							_topicAdmin.erase(itTopic);
							break;
						}
						itTopic++;
					}
					_adminUser.erase(itAdmin);
					break;
				}
				itAdmin++;
			}
			_accesUser.erase(itAcces);
			answer = user + " has been removed from the channel\r\n";
			send_out(socketUser, answer);
			answer = "you have been removed from the channel: #" + channelName + "\r\n";
			send_out(socketNewUser, answer);
			return (true);
		}
		itAcces++;
	}
	answer = user + " doesn't exist in channel\r\n";
	send_out(socketNewUser, answer);
	return (false);
}

void	Channel::cleanUser(std::string user)
{
	std::vector<std::string>::iterator itAcces = _accesUser.begin();
	std::vector<std::string>::iterator itAdmin = _adminUser.begin();
	std::vector<std::string>::iterator itTopic = _topicAdmin.begin();

	while (itAcces != _accesUser.end())
	{
		if (*itAcces == user)
		{
			_accesUser.erase(itAcces);
			break;
		}
		itAcces++;
	}
	while (itAdmin != _adminUser.end())
	{
		if (*itAdmin == user)
		{
			_adminUser.erase(itAdmin);
			break;
		}
		itAdmin++;
	}
	while (itTopic != _topicAdmin.end())
	{
		if (*itTopic == user)
		{
			_topicAdmin.erase(itTopic);
			break;
		}
		itTopic++;
	}
	return;
}

bool	Channel::deleteTopicAdmin(int socketUser, int socketNewUser, std::string user, std::string channelName) {

	std::string answer;
	std::vector<std::string>::iterator itTopic = _topicAdmin.begin();

	while (itTopic != _accesUser.end())
	{
		if (*itTopic == user)
		{
			_topicAdmin.erase(itTopic);
			answer = user + " is not allowed to change the channel topic anymore\r\n";
			send_out(socketUser, answer);
			answer = "you are no longer allowed to change the topic in the channel #" + channelName + "\r\n";
			send_out(socketNewUser, answer);
			return (true);
		}
		itTopic++;
	}
	answer = user + " doesn't exist in channel\r\n";
	send_out(socketNewUser, answer);
	return (false);
}

/* ************************************************************************** */