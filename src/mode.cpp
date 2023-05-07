/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <retcheba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:22:55 by luserbu           #+#    #+#             */
/*   Updated: 2023/05/07 15:39:23 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

void	Server::mode(std::map<int, User>::iterator user, std::string buff) {
	
	size_t pos;
	std::string answer;
	std::string channelName = cleanStringCmd(buff, "MODE #");

	if (checkAlreadyChannel(channelName) == false)
	{
		answer = "channel has not been created\r\n";
		send_out(user->second.getSocket(), answer);
		return;
	}
	pos = buff.find(" -i ");
	if (pos != std::string::npos)
	{
		inviteSetRemove(user, buff, channelName);
		return ;
	}
	pos = buff.find(" -t ");
	if (pos != std::string::npos)
	{
		topicSetRemove(user, buff, channelName);
		return ;
	}
	pos = buff.find(" -k ");
	if (pos != std::string::npos)
	{
		passwordSetRemove(user, buff, channelName);
		return ;
	}
	pos = buff.find(" -o ");
	if (pos != std::string::npos)
	{
		operatorGiveTake(user, buff, channelName);
		return ;
	}
	pos = buff.find(" -l ");
	if (pos != std::string::npos)
	{
		limitSetRemove(user, buff, channelName);
		return ;
	}
	answer = "Usage: MODE <#channel> -i <set/remove>\nUsage: MODE <#channel> -t <set/remove> <nickname>\nUsage: MODE <#channel> -k <set> <password>\nUsage: MODE <#channel> -k <remove>\nUsage: MODE <#channel> -o <give/take> <nickname>\nUsage: MODE <#channel> -l <set> <number>\nUsage: MODE <#channel> -l <remove>\r\n" ;
	send_out(user->second.getSocket(), answer);
}

void	Server::inviteSetRemove(std::map<int, User>::iterator user, std::string buff, std::string channelName) {
	
	std::map<std::string, Channel>::iterator itChan;
	
	size_t pos;
	std::string mode;
	std::string answer;
	
	mode = "MODE #" + channelName + " -i set";
	pos = buff.find(mode);
	if (pos != std::string::npos)
	{
		itChan = findChannelIterator(channelName);
		itChan->second.setInviteOnly(user->second.getSocket(), user->second.getNick(), channelName);
		return ;
	}
	mode = "MODE #" + channelName + " -i remove";
	pos = buff.find(" -i remove");
	if (pos != std::string::npos)
	{
		itChan = findChannelIterator(channelName);
		itChan->second.removeInviteOnly(user->second.getSocket(), user->second.getNick(), channelName);
		return ;
	}
	answer = "Usage: MODE <#channel> -i <set/remove>\r\n";
	send_out(user->second.getSocket(), answer);
}

void	Server::topicSetRemove(std::map<int, User>::iterator user, std::string buff, std::string channelName) {
	
	std::map<std::string, Channel>::iterator itChan;
	std::map<int, User>::iterator itUser;
	
	size_t pos;
	std::string mode;
	std::string answer;
	std::string nickname;
	
	mode = "MODE #" + channelName + " -t set ";
	pos = buff.find(mode);
	if (pos != std::string::npos)
	{
		nickname = buff.substr(mode.length(), buff.length());
		itChan = findChannelIterator(channelName);
		if (itChan->second.findUser(nickname) == false)
		{
			answer = nickname + " is not in channel #" + channelName + "\r\n";
			send_out(user->second.getSocket(), answer);
			return ;
		}
		if (itChan->second.findAdminUser(nickname) == false)
		{
			answer = nickname + " is not admin in channel #" + channelName + "\r\n";
			send_out(user->second.getSocket(), answer);
			return ;
		}
		if (itChan->second.findTopicAdmin(nickname) == true)
		{
			answer = nickname + " already has the rights to the topic #" + channelName + "\r\n";
			send_out(user->second.getSocket(), answer);
			return ;
		}
		itUser = findUserIterator(nickname);
		itChan->second.setTopicAdminOnly(user->second.getSocket(), itUser->second.getSocket(), nickname, channelName);
		return ;
	}
	mode = "MODE #" + channelName + " -t remove ";
	pos = buff.find(mode);
	if (pos != std::string::npos)
	{
		nickname = buff.substr(mode.length(), buff.length());
		itChan = findChannelIterator(channelName);
		if (itChan->second.findUser(nickname) == false)
		{
			answer = nickname + " is not in channel #" + channelName + "\r\n";
			send_out(user->second.getSocket(), answer);
			return ;
		}
		if (itChan->second.findAdminUser(nickname) == false)
		{
			answer = nickname + " is not admin in channel #" + channelName + "\r\n";
			send_out(user->second.getSocket(), answer);
			return ;
		}
		if (itChan->second.findTopicAdmin(nickname) == false)
		{
			answer = nickname + " no longer has the right to the topic #" + channelName + "\r\n";
			send_out(user->second.getSocket(), answer);
			return ;
		}
		itUser = findUserIterator(nickname);
		itChan->second.deleteTopicAdmin(user->second.getSocket(), itUser->second.getSocket(), nickname, channelName);
		return ;
	}
	answer = "Usage: MODE <#channel> -t <set/remove> <nickname>\r\n";
	send_out(user->second.getSocket(), answer);
}

bool 	Server::checkPassword(std::string buff)
{
	int i = 0;
	
	if (buff[0] == '\0')
		return (false);
	for (int l = 0; buff[l] != '\0'; l++)
	{
		if (buff[l] == ' ')
			return (false);
	}
	while (buff[i] != ' ' && buff[i] != '\0' && ( buff[i] > 32 && buff[i] < 127))
		i++;
	if (buff[i] != '\0')
		return (false);
	return (true);
}

void	Server::passwordSetRemove(std::map<int, User>::iterator user, std::string buff, std::string channelName) {

	std::map<std::string, Channel>::iterator itChan;
	
	size_t pos;
	std::string mode;
	std::string answer;
	std::string password;
	
	mode = "MODE #" + channelName + " -k set ";
	pos = buff.find(mode);
	if (pos != std::string::npos)
	{
		password = buff.substr(mode.length(), buff.length());
		if (checkPassword(password) == false)
		{
			answer = "Usage: MODE <#channel> -k set <password>\r\n";
			send_out(user->second.getSocket(), answer);
			return;
		}
		itChan = findChannelIterator(channelName);
		itChan->second.setPassWord(user->second.getSocket(), user->second.getNick(), channelName, password);
		return ;
	}
	mode = "MODE #" + channelName + " -k remove";
	pos = buff.find(mode);
	if (pos != std::string::npos)
	{
		itChan = findChannelIterator(channelName);
		itChan->second.removePassWord(user->second.getSocket(), user->second.getNick(), channelName);
		return ;
	}
	answer = "Usage: MODE <#channel> -k <set> <password>\r\n";
	send_out(user->second.getSocket(), answer);
	answer = "Usage: MODE <#channel> -k <remove>\r\n";
	send_out(user->second.getSocket(), answer);
}

void	Server::operatorGiveTake(std::map<int, User>::iterator user, std::string buff, std::string channelName) {
	
	std::map<std::string, Channel>::iterator itChan;
	std::map<int, User>::iterator itUser;
	
	size_t pos;
	std::string mode;
	std::string answer;
	std::string nickname;
	
	mode = "MODE #" + channelName + " -o give ";
	pos = buff.find(mode);
	if (pos != std::string::npos)
	{
		nickname = buff.substr(mode.length(), buff.length());
		itChan = findChannelIterator(channelName);
		if (itChan->second.findUser(nickname) == false)
		{
			answer = nickname + " are not in channel: #" + channelName + "\r\n";
			send_out(user->second.getSocket(), answer);
			return ;
		}
		itUser = findUserIterator(nickname);
		itChan->second.setAdmin(user->second.getSocket(), itUser->second.getSocket(), nickname);
		return ;
	}
	mode = "MODE #" + channelName + " -o take ";
	pos = buff.find(mode);
	if (pos != std::string::npos)
	{
		nickname = buff.substr(mode.length(), buff.length());
		itChan = findChannelIterator(channelName);
		if (itChan->second.findUser(nickname) == false)
		{
			answer = nickname + " are not in channel: #" + channelName + "\r\n";
			send_out(user->second.getSocket(), answer);
			return ;
		}
		itUser = findUserIterator(nickname);
		itChan->second.removeAdmin(user->second.getSocket(), itUser->second.getSocket(), nickname);
		return ;
	}
	answer = "Usage: MODE <#channel> -o <give/take> <nickname>\r\n";
	send_out(user->second.getSocket(), answer);
}

bool	checkLimitNb(std::string buff) {
	
	char *p;
	double nb;

	nb = strtod(buff.c_str(), &p);
	if (p[0] != '\0')
		return (false);
	if (nb <= 0)
		return (false);
	return (true);
}

void	Server::limitSetRemove(std::map<int, User>::iterator user, std::string buff, std::string channelName) {
	
	std::map<std::string, Channel>::iterator itChan;
	
	char *p;
	size_t pos;
	std::string mode;
	std::string answer;
	std::string number;
	
	mode = "MODE #" + channelName + " -l set ";
	pos = buff.find(mode);
	if (pos != std::string::npos)
	{
		number = buff.substr(mode.length(), buff.length());
		if (checkLimitNb(number) == false)
		{
			answer = "Usage: MODE <#channel> -l set <number>\nNumber must be superior than zero\r\n";
			send_out(user->second.getSocket(), answer);
			return;
		}
		itChan = findChannelIterator(channelName);
		itChan->second.setMaxUser(user->second.getSocket(), user->second.getNick(), channelName, strtod(number.c_str(), &p));
		return ;
	}
	mode = "MODE #" + channelName + " -l remove";
	pos = buff.find(mode);
	if (pos != std::string::npos)
	{
		itChan = findChannelIterator(channelName);
		itChan->second.removeMaxUser(user->second.getSocket(), user->second.getNick(), channelName);
		return ;
	}
	answer = "Usage: MODE <#channel> -l <set> <number>\r\n";
	send_out(user->second.getSocket(), answer);
	answer = "Usage: MODE <#channel> -l <remove>\r\n";
	send_out(user->second.getSocket(), answer);
}
