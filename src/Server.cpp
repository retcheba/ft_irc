/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:51:15 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/02 20:22:16 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

Server::Server( void )
{
    return;
}

Server::Server( Server const & src )
{
    (void)src;
    return;
}

Server::~Server( void )
{
    return;
}

Server &    Server::operator=( Server const & rhs )
{
    (void)rhs;
    return (*this);
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

void    Server::process( std::string username )
{
	size_t pos;
	(void) username;
    if ( this->_buff.empty() )
    {
        std::cerr << "Error: message is empty" << std::endl;
    }
	pos = _buff.find("SEND");
	if (pos != std::string::npos)
		std::cout << "find SEND" << std::endl;
	pos = _buff.find("JOIN");
	if (pos != std::string::npos)
		std::cout << "find JOIN" << std::endl;
	pos = _buff.find("CHANNEL");
	if (pos != std::string::npos)
		std::cout << "find CHANNEL" << std::endl;
	pos = _buff.find("NICKNAME");
	if (pos != std::string::npos)
		std::cout << "find NICKNAME" << std::endl;
	return;
}