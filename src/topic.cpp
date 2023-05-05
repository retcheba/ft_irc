/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luserbu <luserbu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:33:20 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/05 23:02:17 by luserbu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

bool 	Server::checkLastMessage(std::string buff, std::string cmd)
{
	size_t pos;

	pos = buff.find(cmd);
	if (pos == std::string::npos)
		return (false);
	while (buff[pos] != ' ' && buff[pos] != '\0' && ( buff[pos] > 32 && buff[pos] < 127))
		pos++;
	if (buff[pos] != ' ')
		return (false);
	if (buff[pos + 1] == '\0')
		return (false);
	return (true);
}

bool 	checkFormatTopic(std::string buff, std::string cmd)
{
	size_t pos;

	pos = buff.find(cmd);
	if (pos == std::string::npos)
		return (false);
	while (buff[pos] != ' ' && buff[pos] != '\0' && ( buff[pos] > 32 && buff[pos] < 127))
		pos++;
	if (buff[pos] != '\0')
		return (false);
	return (true);
}

std::string 	cleanLastMessage(std::string buff, std::string cmd)
{
	size_t start;
	size_t pos;
	std::string clean;
	
	pos = buff.find(cmd);
	while (buff[pos] != ' ' && buff[pos] != '\0' && ( buff[pos] > 32 && buff[pos] < 127))
		pos++;
	pos++;
	start = pos;
	while (buff[pos] != ' ' && buff[pos] != '\0' && ( buff[pos] > 32 && buff[pos] < 127))
		pos++;
	clean = buff.substr(start, pos);
	return (clean);
}

void	Server::topic(std::map<int, User>::iterator user, std::string buff) {

	size_t pos;	
	std::string answer;
	
	
	std::cout << buff << std::endl;
	pos = buff.find("view");
	if (pos != std::string::npos)
	{
		topicView(user, buff);
		return ;
	}
	pos = buff.find("change");
	if (pos != std::string::npos)
	{
		topicChange(user, buff);
		return ;
	}
	answer = "Usage: TOPIC <#channel> <view/change> <topic>\r\n";
	send_out(user->second.getSocket(), answer);
}

void	Server::topicView(std::map<int, User>::iterator user, std::string buff) {
	
	std::map<std::string, Channel>::iterator itChan;

	std::string answer;
	std::string topic;
	std::string channelName;
	
	channelName = cleanStringCmd(buff, "TOPIC #");
	if (checkAlreadyChannel(channelName) == false)
	{
		answer = "channel has not been created\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	if (checkFormatTopic(buff, "view") == false)
	{
		answer = "Usage: TOPIC <#channel> <view> <topic>\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	itChan = findChannelIterator(channelName);

	if (itChan->second.findUser(user->second.getSocket(), user->second.getNick(), channelName) == false)
		return;
	
	if (itChan->second.getTopic() == "")
	{
		answer = "There are not topic in channel #" + channelName + "\r\n";
		send_out(user->second.getSocket(), answer);
		return ;
	}
	topic = itChan->second.getTopic();	
	answer = "Topic #" + channelName + ": " + topic + "\r\n";
	send_out(user->second.getSocket(), answer);
}

void	Server::topicChange(std::map<int, User>::iterator user, std::string buff) {
	
	std::map<std::string, Channel>::iterator itChan;

	std::string answer;
	std::string topic;
	std::string channelName;

	channelName = cleanStringCmd(buff, "TOPIC #");
	if (checkAlreadyChannel(channelName) == false)
	{
		answer = "channel has not been created\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	if (checkLastMessage(buff, "change") == false)
	{
		answer = "Usage: TOPIC <#channel> <change> <topic>\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	itChan = findChannelIterator(channelName);

	if (itChan->second.findUser(user->second.getSocket(), user->second.getNick(), channelName) == false)
		return;
	
	if (itChan->second.modeTopicAdminOnly() == false)
	{
		if (itChan->second.findAdminUser(user->second.getSocket(), user->second.getNick(), channelName) == false)
		{
			answer = "You are not admin to change topic\r\n"; 
			send_out(user->second.getSocket(), answer);
			return ;
		}
	}
	
	topic = cleanLastMessage(buff, "change");
	
	itChan->second.addTopic(topic);
	
	std::map<int, User>::iterator it = this->_clients.begin();
	while (it != this->_clients.end())
	{
		if (itChan->second.findUser(user->second.getSocket(), user->second.getNick(), channelName) == true)
		{
			answer = "#" + channelName + " have new topic: " + topic + "\r\n"; 
			send_out(it->second.getSocket(), answer);
		}
		it++;
	}
}