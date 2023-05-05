/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:51:15 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/05 21:29:53 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

Server::Server( void )
{
    return;
}

Server::~Server( void )
{
    return;
}

void    Server::setPassword( std::string password )
{
    this->_password = password;
    return;
}

std::string Server::getPassword( void )
{
    return (this->_password);
}

void    Server::newClient( int sockId, int sock, std::string username, std::string nickname )
{	
	User user(username, nickname, sock);

	_clients.insert(std::pair<int, User>(sockId, user));
	return;
}

void	Server::deleteClient( int sock )
{
	std::map<int, User>::iterator it = _clients.find(sock);
	
	this->_clients.erase(it);
}

void	Server::deleteAllClient( void )
{
	this->_clients.clear();
	return;
}

std::string Server::getUsername( int sock )
{
	std::map<int, User>::iterator it = _clients.find(sock);
	
	return (it->second.getUser());
}

void    Server::setBuff( std::string buff )
{
    this->_buff = buff;
    return;
}

void    Server::clearBuff( void )
{
    this->_buff.clear();
    return;
}

void	Server::setSock(int sock) {
	
	this->_sock = sock;
    return;
}

int 	Server::alreadyNickname(std::string buff)
{	
	std::map<int, User>::iterator user = _clients.begin();
	
	while (user != _clients.end())
	{
		if (user->second.getNick() == buff)
			return (0);
		user++;
	}
	return (1);
}

void    Server::process( int socket )
{
	std::map<int, User>::iterator user = _clients.find(socket);
	size_t pos;

	if ( ( pos = _buff.find("SEND #") ) != std::string::npos )
		sendMessageChannel(user, this->_buff);
	else if ( ( pos = _buff.find("SEND") ) != std::string::npos )
		sendMessagePrivate(user, this->_buff);
	else if ( ( pos = _buff.find("JOIN") ) != std::string::npos )
		createChannel(user, this->_buff);
	else if ( ( pos = _buff.find("KICK") ) != std::string::npos )
		kickChannel(user, this->_buff);
	else
		send_out((socket + this->_sock), "Accepted commands:\n- private message\n * 'SEND <nickname> <message>'\n- channel\n * 'JOIN <#channel>'\n * 'SEND <#channel> <message>'\n * 'KICK <#channel> <nickname>'\n * 'INVITE <#channel> <nickname>'\n * 'TOPIC <#channel>'\n * 'TOPIC <#channel> <topic>'\n * 'MODE -(i, t, k, o) <#channel>'\r\n");
	return;
}
