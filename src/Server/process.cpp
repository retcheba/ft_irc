/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:12:18 by retcheba          #+#    #+#             */
/*   Updated: 2023/05/08 15:20:42 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void    Server::process( int socket )
{
	std::map<int, User>::iterator user = _clients.find(socket);
	size_t pos;

	if ( ( pos = _buff.find("SEND #") ) != std::string::npos )
		sendMessageChannel(user, this->_buff);
	else if ( ( pos = _buff.find("SEND ") ) != std::string::npos )
		sendMessagePrivate(user, this->_buff);
	else if ( ( pos = _buff.find("JOIN #") ) != std::string::npos )
		createChannel(user, this->_buff);
	else if ( ( pos = _buff.find("KICK #") ) != std::string::npos )
		kickChannel(user, this->_buff);
	else if ( ( pos = _buff.find("TOPIC #") ) != std::string::npos )
		topic(user, this->_buff);
	else if ( ( pos = _buff.find("MODE #") ) != std::string::npos )
		mode(user, this->_buff);
	else if ( ( pos = _buff.find("INVITE #") ) != std::string::npos )
		invite(user, this->_buff);
	else
		send_out((socket + this->_sock), "Accepted commands:\n- private message\n * SEND\n- channel\n * JOIN\n * SEND\n * KICK\n * INVITE\n * TOPIC\n * MODE\r\n");
	return;
}