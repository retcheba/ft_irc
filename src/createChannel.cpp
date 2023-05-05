/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createChannel.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:53:04 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/05 21:03:57 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

static int 	checkFormatJoin(std::string buff)
{
	int i = 5;
	size_t pos;
	std::string user;

	pos = buff.find("JOIN #");
	if (pos == std::string::npos || pos != 0)
		return (0);
	while (buff[i] != ' ' && buff[i] != '\0' && ( buff[i] > 32 && buff[i] < 127))
		i++;
	if (buff[i] != '\0')
		return (0);
	return (1);
}

int 	Server::checkAlreadyChannel(std::string buff)
{	
	std::map<std::string, Channel>::iterator it = _channel.begin();
	
	while (it != _channel.end())
	{
		if (it->first == buff)
			return (true);
		it++;
	}
	return (false);
}

std::map<std::string, Channel>::iterator 	Server::findChannelIterator(std::string channelName)
{	
	std::map<std::string, Channel>::iterator it = _channel.begin();
	
	while (it != _channel.end())
	{
		if (it->first == channelName)
			return (it);
		it++;
	}
	return (it);
}

void		Server::createChannel(std::map<int, User>::iterator user, std::string buff) {
	
	std::map<std::string, Channel>::iterator itChan;
	
	std::string channelName = cleanString(buff, "JOIN #");
	std::string answer;
	
	if (!checkFormatJoin(buff))
	{
		answer = "Usage: JOIN <#channel\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	if (checkAlreadyChannel(channelName) == true)
	{
		itChan = findChannelIterator(channelName);
		
		if (itChan->second.getAccesUser(user->second.getSocket(), channelName) == true)
			return;
			
		itChan->second.addUser(user->second.getSocket(), user->second.getNick(), channelName);
		return;
	}
	Channel chan(user->second.getSocket(), user->second.getNick(),channelName);

	this->_channel.insert(std::pair<std::string, Channel>(channelName, chan));
	return;
}


// void		Server::createChannel(std::map<int, User>::iterator user, std::string buff) {
	
// 	std::map<std::string, Channel>::iterator itChan;
// 	std::string channelName = cleanString(buff, "JOIN #");
// 	std::string answer;
	
// 	if (!checkFormatJoin(buff))
// 	{
// 		answer = "Usage: JOIN <#channel\r\n";
// 		send_out(user->second.getSocket(), answer);
// 		// if (send(user->second.getSocket(), "Usage: JOIN <#channel\r\n", 24, 0) == -1)
// 		// 	std::cerr << "Error: Message can't be sent" << std::endl;
// 		return;
// 	}
// 	if (checkAlreadyChannel(channelName) == true)
// 	{
// 		itChan = findChannelIterator(channelName);
// 		if (itChan->second.getAccesUser(user->second.getSocket(), channelName) == true)
// 			return;
// 		// if (user->second.findChannel(channelName) == true)
// 		// {
// 		// 	answer = "You are already in channel #" + channelName + "\r\n";
// 		// 	if (send(user->second.getSocket(), answer.c_str(), answer.length(), 0) == -1)
// 		// 		std::cerr << "Error: Message can't be sent" << std::endl;
// 		// 	return;
// 		// }
// 		itChan->second.addUser(user->second.getSocket(), user->second.getNick(), channelName);
// 		// user->second.setChan(channelName, false);
// 		// answer = "You have join channel #" + channelName + "\r\n";
// 		// if (send(user->second.getSocket(), answer.c_str(), answer.length(), 0) == -1)
// 		// 	std::cerr << "Error: Message can't be sent" << std::endl;
// 		return;
// 	}
// 	Channel chan(user->second.getSocket(), user->second.getNick(),channelName);

// 	this->_channel.insert(std::pair<std::string, Channel>(channelName, chan));
// 	// _channel.push_back(channelName);
// 	// user->second.setChan(channelName, true);
// 	// answer = "Channel: #" + channelName + " has been created\r\n";
	
// 	// if (send(user->second.getSocket(), answer.c_str(), answer.length(), 0) == -1)
// 	// 	std::cerr << "Error: Message can't be sent" << std::endl;
// 	return;
// }