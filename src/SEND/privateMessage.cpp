/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privateMessage.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:47:03 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/07 16:47:12 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void	Server::sendMessagePrivate(std::map<int, User>::iterator user, std::string buff)
{	
	size_t pos;
    std::string clean = cleanString(buff, "SEND ");

	if (( pos = _buff.find("SEND") ) != 0 )
	{
		send_out(user->second.getSocket(), "Usage: SEND <nickname> <message>\r\n" );
        return;
	}
    if (!checkFormatMessage(buff, "SEND ", 5))
    {
        send_out(user->second.getSocket(), "Usage: SEND <nickname> <message>\r\n" );
        return;
    }
    for ( std::map<int, User>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++ )
    {
        pos = clean.find(it->second.getNick());
        if (pos != std::string::npos)
        {
            clean = cleanString(clean, (it->second.getNick() + " "));
            clean = user->second.getNick() + " : " + clean + "\r\n";

            send_out(it->second.getSocket(), clean);
            break;
        }
    }
    if (pos == std::string::npos)
        send_out(user->second.getSocket(), "Error : Nickname not found\r\n");
}