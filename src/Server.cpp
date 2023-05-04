/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:51:15 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/04 14:35:05 by luserbu          ###   ########.fr       */
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
	std::map<int, User>::iterator it = _clients.find(socket);
	size_t pos;
	

	if ( this->_buff.empty() )
        std::cerr << "Error: message is empty" << std::endl;
	else if ( ( pos = _buff.find("SEND") ) != std::string::npos )
		sendMessage(it->second.getUser(), this->_buff, socket);
	else if ( ( pos = _buff.find("JOIN") ) != std::string::npos )
		std::cout << "find JOIN" << std::endl;
	else if ( ( pos = _buff.find("CHANNEL") ) != std::string::npos )
		std::cout << "find CHANNEL" << std::endl;
	else
	{
		if (send(socket, "The only accepted commands are: SEND, JOIN or CHANNEL\n", 65, 0) == -1)
			std::cerr << "Error Message can't be sent" << std::endl;
	}
	return;
}