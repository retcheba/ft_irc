/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:15:51 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/07 16:16:19 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"

/*
** --------------------------------- GETTER ----------------------------------
*/

std::string 	Channel::getTopic() {
	
	return (this->_topic);
}

std::string 	Channel::getPassword() {
	
	return (this->_password);
}

int		Channel::channelSize() {
	
	return (_accesUser.size());
}

double			Channel::getMaxUser() {
	
	return (this->_maxUser);
}

std::vector<std::string> &	Channel::getAcUser( void )
{
	return (this->_accesUser);
}

std::vector<std::string> &	Channel::getAdUser( void )
{
	return (this->_adminUser);
}

std::vector<std::string> &	Channel::getTopicAdmin( void )
{
	return (this->_topicAdmin);
}

bool		Channel::getAccesUser(int socketUser, std::string channelName) {
	
	std::string answer;
	std::vector<std::string>::iterator itAcces = _accesUser.begin();

	while (itAcces != _accesUser.end())
	{
		if (*itAcces == channelName)
		{
			answer = "You are already in channel #" + channelName + "\r\n";
			send_out(socketUser, answer);
			return (true);
		}
		itAcces++;
	}
	return (false);
}

/* ************************************************************************** */