/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:38 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/05 14:38:26 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/User.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

User::User()
{
}

User::	User(std::string user, std::string nick, int sock) : _username(user), _nickname(nick), _socket(sock)
{
	_index = 0;
}
/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

User::~User()
{
}

/*
** --------------------------------- METHODS ----------------------------------
*/

// GETTER
std::string User::getUser(void) {
	
	return (this->_username);
}

std::string User::getNick(void) {

	return (this->_nickname);
}


int			User::getSocket(void) {

	return (this->_socket);
}

// SETTER
void		User::setUser(std::string user) {

	this->_username = user;
}

void		User::setNick(std::string nick) {

	this->_nickname = nick;
}

void		User::setChan(std::string chan, bool admin) {
	
	int rule;
	
	if (admin == true)
		rule = 1;
	else
		rule = -1;
	
	_channelStr[_index] = chan;
	_channelIdx[_index] = rule;
	_index += 1;
}

void		User::setSocket(int sock) {

	this->_socket = sock;
}

bool User::findChannel(std::string chan) {
	
	for (int i = 0; i < _index; i++)
	{
		if (_channelStr[i] == chan)
			return (true);
	}
	return (false);
}

bool		User::checkAdminChannel(std::string chan) {
	
	for (int i = 0; i < _index; i++)
	{
		if (_channelStr[i] == chan)
		{
			if (_channelIdx[i] == 1)
				return (true);
			else
				return (false);
		}
	}
	return (false);
}

void		User::deleteChannel(std::string chan) {
	
	for (int i = 0; i < _index; i++)
	{
		if (_channelStr[i] == chan)
		{
			for (size_t l = 0; l < _channelStr[i].length(); l++)
				_channelStr[i][l] = '\0';
		}
	}
	
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */