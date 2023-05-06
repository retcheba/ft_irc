/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sendMessage.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:17:31 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/06 19:54:59 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"
	
std::string	 Server::cleanString(std::string buff, std::string remove)
{
	size_t pos;
	
	pos = buff.find(remove);
	if (pos != std::string::npos)
		buff.erase(pos, remove.length());
	return (buff);	
}

std::string	 Server::cleanStringCmd(std::string buff, std::string remove)
{
	int i = 0;
	size_t pos;
	std::string clean;
	
	pos = buff.find(remove);
	if (pos != std::string::npos)
		buff.erase(pos, remove.length());
	while (buff[i] != ' ' && buff[i] != '\0' && ( buff[i] > 32 && buff[i] < 127))
		i++;
	clean = buff.substr(0, i);
	return (clean);
}

bool 	Server::checkFormatMessage(std::string buff, std::string remove, int i)
{
	size_t pos;
	std::string user;

	pos = buff.find(remove);
	if (pos == std::string::npos || pos != 0)
		return (false);
	while (buff[i] != ' ' && buff[i] != '\0' && ( buff[i] > 32 && buff[i] < 127))
		i++;
	if (buff[i] != ' ')
		return (false);
	if (buff[i + 1] == '\0')
		return (false);
	return (true);
}

void	Server::sendMessagePrivate(std::map<int, User>::iterator user, std::string buff)
{	
	size_t pos;
    std::string clean = cleanString(buff, "SEND ");

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

void	Server::sendMessageChannel(std::map<int, User>::iterator user, std::string buff) {	

	std::map<std::string, Channel>::iterator itChan;
			
	std::string answer;
	std::string message;
	std::string channelName;
	
	if (!checkFormatMessage(buff, "SEND #", 6))
	{
		answer = "Usage: SEND <#channel> <message>\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	channelName = cleanStringCmd(buff, "SEND #");
	if (checkAlreadyChannel(channelName) == false)
	{
		answer = "channel has not been created\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	itChan = findChannelIterator(channelName);

	if (itChan->second.findUser(user->second.getNick()) == false)
	{
		answer = "You have not join the channel #" + channelName + "\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}

	std::map<int, User>::iterator it = this->_clients.begin();
	while (it != this->_clients.end())
	{
		if (itChan->second.findUser(it->second.getNick()) == true)
		{
			message = buff.substr(( strlen("SEND #") + channelName.length() + 1 ), buff.length());
			answer = "#" + channelName + " " + user->second.getNick() + ": " + message + "\r\n"; 
			send_out(it->second.getSocket(), answer);
		}
		it++;
	}
}

// void	Server::sendMessageChannel(std::map<int, User>::iterator user, std::string buff) {	

// 	std::map<std::string, Channel>::iterator itChan;
			
// 	std::string answer;
// 	std::string message;
// 	std::string channelName;
	
// 	if (!checkFormatMessage(buff, "SEND #", 6))
// 	{
// 		answer = "Usage: SEND <#channel> <message>\r\n";
// 		send_out(user->second.getSocket(), answer);
// 		return;
// 	}
// 	channelName = cleanStringCmd(buff, "SEND #");
// 	if (checkAlreadyChannel(channelName) == false)
// 	{
// 		answer = "channel has not been created\r\n";
// 		send_out(user->second.getSocket(), answer);
// 		return;
// 	}
// 	itChan = findChannelIterator(channelName);
// 	if (itChan->second.findUser(user->second.getSocket(), user->second.getNick(), channelName) == false)
// 		return;
// 	// if (user->second.findChannel(channelName) == false)
// 	// {
// 	// 	answer = "You have not join the channel #" + channelName + "\r\n";
// 	// 	send_out(user->second.getSocket(), answer);
// 	// 	return;
// 	// }
// 	std::map<int, User>::iterator it = this->_clients.begin();
// 	while (it != this->_clients.end())
// 	{
// 		// if (it->second.findChannel(channelName) == true)
// 		// {
// 		// 	message = buff.substr(( strlen("SEND #") + channelName.length() + 1 ), buff.length());
// 		// 	answer = "#" + channelName + " " + user->second.getNick() + ": " + message + "\r\n"; 
// 		// 	send_out(it->second.getSocket(), answer);
// 		// }
// 		if (itChan->second.findUser(user->second.getSocket(), user->second.getNick(), channelName) == true)
// 		{
// 			message = buff.substr(( strlen("SEND #") + channelName.length() + 1 ), buff.length());
// 			answer = "#" + channelName + " " + user->second.getNick() + ": " + message + "\r\n"; 
// 			send_out(it->second.getSocket(), answer);
// 		}
// 		it++;
// 	}
// }