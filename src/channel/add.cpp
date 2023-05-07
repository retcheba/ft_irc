/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:09:00 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/07 16:10:14 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"

/*
** --------------------------------- ADD ----------------------------------
*/

void	Channel::addTopic(std::string topic) {

	this->_topic = topic;
}

void	Channel::addPassword(std::string password) {

	this->_password = password;
}

bool	Channel::addUser(int socketUser, std::string user, std::string channelName) {

	std::string answer;
	std::vector<std::string>::iterator itAcces = _accesUser.begin();

	while (itAcces != _accesUser.end())
	{
		if (*itAcces == user)
		{
			answer = user + " is already in the channel\r\n";
			send_out(socketUser, answer);
			return (false);
		}
		itAcces++;
	}
	_accesUser.push_back(user);
	answer = "You have join the channel #" + channelName + "\r\n";
	send_out(socketUser, answer);
	return (true);
}

/* ************************************************************************** */