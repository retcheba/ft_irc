// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   kickChannel.cpp                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/05/04 18:29:55 by luserbu           #+#    #+#             */
// /*   Updated: 2023/05/04 19:17:48 by luserbu          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../inc/Server.hpp"

// void	Server::kickChannel(std::map<int, User>::iterator user, std::string buff) {
	
// 	std::string answer;
// 	std::string userName;
// 	std::string channelName;
	
// 	if (!checkFormatMessage(buff, "KICK  #", 7))
// 	{
// 		if (send(user->second.getSocket(), "Usage: KICK <#channel> <nickname>\n", 35, 0) == -1)
// 			std::cerr << "Error Message can't be sent" << std::endl;
// 		return;
// 	}
// 	channelName = cleanStringCmd(buff, "KICK #");
// 	if (checkAlreadyChannel(channelName) == false)
// 	{
// 		if (send(user->second.getSocket(), "channel has not been created\n", 30, 0) == -1)
// 			std::cerr << "Error Message can't be sent" << std::endl;
// 		return;
// 	}
// 	if (user->second.findChannel(channelName) == false)
// 	{
// 		answer = "You have not join the channel <" + channelName + ">\n";
// 		if (send(user->second.getSocket(), answer.c_str(), answer.length(), 0) == -1)
// 			std::cerr << "Error Message can't be sent" << std::endl;
// 		return;
// 	}
// 	if (user->second.checkAdminChannel(channelName) == false)
// 	{
// 		answer = "You have not admin in channel: <" + channelName + ">\n";
// 		if (send(user->second.getSocket(), answer.c_str(), answer.length(), 0) == -1)
// 			std::cerr << "Error Message can't be sent" << std::endl;
// 		return;
// 	}
// 	userName = buff.substr(( strlen("SEND #") + channelName.length() + 1 ), buff.length());
// 	std::map<int, User>::iterator it = this->_clients.begin();
// 	while (it != this->_clients.end())
// 	{
// 		if (it->second.getNick() == userName)
// 		{
// 			it->second.deleteChannel(channelName);
// 		}
// 	}
	
	
// }

// // void	Server::sendMessageChannel(std::map<int, User>::iterator user, std::string buff) {	
		
// // 	std::string answer;
// // 	std::string message;
// // 	std::string channelName;
	
// // 	if (!checkFormatMessage(buff, "SEND #", 6))
// // 	{
// // 		if (send(user->second.getSocket(), "Usage: SEND <#channel> <message>\n", 34, 0) == -1)
// // 			std::cerr << "Error Message can't be sent" << std::endl;
// // 		return;
// // 	}
// // 	channelName = cleanStringCmd(buff, "SEND #");
// // 	if (checkAlreadyChannel(channelName) == false)
// // 	{
// // 		if (send(user->second.getSocket(), "channel has not been created\n", 30, 0) == -1)
// // 			std::cerr << "Error Message can't be sent" << std::endl;
// // 		return;
// // 	}
// // 	if (user->second.findChannel(channelName) == false)
// // 	{
// // 		answer = "You have not join the channel <" + channelName + ">\n";
// // 		if (send(user->second.getSocket(), answer.c_str(), answer.length(), 0) == -1)
// // 			std::cerr << "Error Message can't be sent" << std::endl;
// // 		return;
// // 	}
// // 	std::map<int, User>::iterator it = this->_clients.begin();
// // 	while (it != this->_clients.end())
// // 	{
// // 		if (it->second.findChannel(channelName) == true)
// // 		{
// // 			message = buff.substr(( strlen("SEND #") + channelName.length() + 1 ), buff.length());
// // 			answer = "#" + channelName + " " + user->second.getNick() + ": " + message + "\n"; 
// // 			if (send(it->second.getSocket(), answer.c_str(), answer.length(), 0) == -1)
// // 				std::cerr << "Error Message can't be sent" << std::endl;
// // 		}
// // 		it++;
// // 	}
// // }