/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:01:38 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/06 17:14:24 by luserbu          ###   ########.fr       */
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
	// _index = 0;
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

void		User::setSocket(int sock) {

	this->_socket = sock;
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */