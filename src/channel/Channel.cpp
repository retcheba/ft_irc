/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:16:15 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/07 16:22:00 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"

/*
** -------------------------- CONSTRUCTOR / DESTRUCTOR----------------------------
*/

Channel::Channel()
{
}

Channel::Channel(int socketUser, std::string User, std::string channelName)
{
	std::string answer;
	
	_adminUser.push_back(User);
	_accesUser.push_back(User);
	_topicAdmin.push_back(User);

	this->_maxUser = 0;

	this->maxUserSet = false;
	this->inviteOnly = false;
	this->passwordSet = false;

	answer = "Channel: #" + channelName + " has been created\r\n";
	send_out(socketUser, answer);
	
}

Channel::~Channel()
{
}

/* ************************************************************************** */