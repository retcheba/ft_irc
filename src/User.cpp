/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:38 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/04 19:17:08 by luserbu          ###   ########.fr       */
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
		rule = 0;
	
	_channel.insert(std::pair<int, std::string>(rule, chan));
	
}

void		User::setSocket(int sock) {

	this->_socket = sock;
}

bool User::findChannel(std::string chan) {
	
	std::map<int, std::string>::iterator it = _channel.begin();
	
	while (it != _channel.end())
	{
		if (it->second == chan)
			return (true);
		it++;
	}
	return (false);
}

bool		User::checkAdminChannel(std::string chan) {
	
	std::map<int, std::string>::iterator it = _channel.begin();

	while (it != _channel.end())
	{
		if (it->second == chan)
		{
			if (it->first == 1)
				return (true);
			else
				return (false);	
		}
		it++;
	}
	return (false);
}

void		User::deleteChannel(std::string chan) {
	
	std::map<int, std::string>::iterator it = _channel.begin();
	
	while (it != _channel.end())
	{
		if (it->second == chan)
		{
			_channel.erase(it);
			break;
		}
		it++;
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */