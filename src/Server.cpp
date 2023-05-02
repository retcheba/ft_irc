/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:51:15 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/02 16:45:45 by retcheba         ###   ########.fr       */
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
}

std::string Server::getUsername( int sock )
{
    std::map<int, std::string>::iterator    it = this->_clients.begin();
    std::map<int, std::string>::iterator    ite = this->_clients.end();

    while (it != ite)
    {
        if ( it->first == sock )
            return ( it->second );
        it++;
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
    if ( this->_buff.empty() )
    {
        std::cerr << "Error: message is empty" << std::endl;
    }
    std::cout << username << ": " << this->_buff << std::endl;
}