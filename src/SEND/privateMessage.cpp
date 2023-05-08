/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privateMessage.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:47:03 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/08 16:17:26 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void	Server::sendMessagePrivate(std::map<int, User>::iterator user, std::string buff)
{	
    std::map<int, User>::iterator itUser;
    
	size_t pos;
    std::string answer;
    std::string message;
    std::string nickname = cleanStringCmd(buff, "SEND ");

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
    if (checkAlreadyUser(nickname) == false)
    {
        send_out(user->second.getSocket(), "Error : Nickname not found\r\n");
    }
    itUser = findUserIterator(nickname);
    
    for ( std::map<int, User>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++ )
    {
        if (it->second.getNick() == nickname)
        {
            message = buff.substr(( strlen("SEND ") + nickname.length() + 1 ), buff.length());
            answer = nickname + " : " + message + "\r\n";
            send_out(it->second.getSocket(), answer);
            return ;
        }
    }
}