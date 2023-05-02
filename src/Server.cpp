/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:51:15 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/02 22:25:19 by luserbu          ###   ########.fr       */
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

void    Server::newClient( int sock, std::string username )
{
    this->_clients.insert( std::pair<int, std::string>( sock, username) );
	return;
}

void	Server::deleteClient( int sock )
{
	std::map<int, std::string>::iterator    ite = this->_clients.end();

	for ( std::map<int, std::string>::iterator it = this->_clients.begin(); it != ite; it++ )
	{
		if ( it->first == sock )
		{
			this->_clients.erase(it);
			break;
		}
	}
	return;
}

void	Server::deleteAllClient( void )
{
	this->_clients.clear();
	return;
}

std::string Server::getUsername( int sock )
{
	std::map<int, std::string>::iterator    ite = this->_clients.end();

	for ( std::map<int, std::string>::iterator it = this->_clients.begin(); it != ite; it++ )
	{
		if ( it->first == sock )
			return ( it->second );
	}
    return ("Client");
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

void    Server::process( std::string username, int socket )
{
	size_t pos;

	if ( this->_buff.empty() )
        std::cerr << "Error: message is empty" << std::endl;
	else if ( ( pos = _buff.find("SEND") ) != std::string::npos )
		sendMessage(username, this->_buff, socket);
	else if ( ( pos = _buff.find("JOIN") ) != std::string::npos )
		std::cout << "find JOIN" << std::endl;
	else if ( ( pos = _buff.find("CHANNEL") ) != std::string::npos )
		std::cout << "find CHANNEL" << std::endl;
	else if ( ( pos = _buff.find("NICKNAME") ) != std::string::npos )
		std::cout << "find NICKNAME" << std::endl;
	else
	{
		if (send(socket, "The only accepted commands are: SEND, JOIN, CHANNEL or NICKNAME\n", 65, 0) == -1)
			std::cerr << "Error Message can't be sent" << std::endl;
	}
	return;
}